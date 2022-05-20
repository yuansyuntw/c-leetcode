int gHeapSize = 50000;

bool isEnableDebug = true;
bool gIsMaxHeap = true;
bool gIsMinHeap = false;

typedef struct {
    int rightHeapCount;
    int* rightHeap;     // min heap
    int leftHeapCount;
    int* leftHeap;      // max heap
} MedianFinder;

void swap(int* heap, int index1, int index2) {
    int temp = heap[index1];
    heap[index1] = heap[index2];
    heap[index2] = temp;
}

void heapify(int* heap, int maxIndex, int index, bool isMaxHeapify) {
    int leftChildIndex = (2*index) + 1;
    int rightChildIndex = (2*index) + 2;
    
    int top = index;
    if (isMaxHeapify) {
        // max heapify
        if (leftChildIndex < maxIndex) {
            if (heap[leftChildIndex] > heap[top]) {
                top = leftChildIndex;
            }
        }

        if (rightChildIndex < maxIndex) {
            if (heap[rightChildIndex] > heap[top]) {
                top = rightChildIndex;
            }
        }
    } else {
        // min heapify
        if (leftChildIndex < maxIndex) {
            if (heap[leftChildIndex] < heap[top]) {
                top = leftChildIndex;
            }
        }

        if (rightChildIndex < maxIndex) {
            if (heap[rightChildIndex] < heap[top]) {
                top = rightChildIndex;
            }
        }
    }
    
    if (top != index) {
        swap(heap, index, top);
        heapify(heap, maxIndex, top, isMaxHeapify);
    }
}

int extractTop(int* heap, int* count, bool isMaxHeap) {
    if ((*count) == 0) {
        printf("Fail to extract min heap, becasuse the count is zero\n");
        return 0;
    }
    
    int result = heap[0];
    (*count)--;
    
    if ((*count) > 0) {
        // pick the last one to the first one.
        heap[0] = heap[*count];
        heapify(heap, *count, 0, isMaxHeap);
    }
    
    return result;
}

void heapInsert(int* heap, int* count, int value, bool isMaxHeap) {
    if ((*count) >= gHeapSize) {
        printf("Fail to insert value to min heap, becasue the size of array is not enought\n");
        return;
    }
    
    int index = *count;
    heap[index] = value;
    (*count)++;
    
    int parent = (index-1)/2;
    while (parent >= 0) {
        if ((isMaxHeap && (heap[index] > heap[parent])) ||
            (!isMaxHeap && (heap[index] < heap[parent]))) {
            swap(heap, index, parent);
            index = parent;
            parent = (index-1)/2;
        } else {
            break;
        }
    }
}

MedianFinder* medianFinderCreate() {
    MedianFinder *finder = calloc(sizeof(MedianFinder), 1);
    finder->rightHeapCount = 0;
    finder->rightHeap = calloc(sizeof(int), gHeapSize/2);
    finder->leftHeapCount = 0;
    finder->leftHeap = calloc(sizeof(int), gHeapSize/2);
    return finder;
}

void medianFinderAddNum(MedianFinder* obj, int num) {
    heapInsert(obj->leftHeap, &obj->leftHeapCount, num, gIsMaxHeap);
    
    // if any node of left heap is larger than right heap
    if ((obj->leftHeapCount > 0) && (obj->rightHeapCount > 0) && (obj->leftHeap[0] > obj->rightHeap[0])) {
        int right = extractTop(obj->leftHeap, &obj->leftHeapCount, gIsMaxHeap);
        heapInsert(obj->rightHeap, &obj->rightHeapCount, right, gIsMinHeap);
    }
    
    // check the size of heap
    if (obj->leftHeapCount > (obj->rightHeapCount + 1)) {
        int right = extractTop(obj->leftHeap, &obj->leftHeapCount, gIsMaxHeap);
        heapInsert(obj->rightHeap, &obj->rightHeapCount, right, gIsMinHeap);
    }
    
    if (obj->rightHeapCount > (obj->leftHeapCount + 1)) {
        int left = extractTop(obj->rightHeap, &obj->rightHeapCount, gIsMinHeap);
        heapInsert(obj->leftHeap, &obj->leftHeapCount, left, gIsMaxHeap);
    }
}

double medianFinderFindMedian(MedianFinder* obj) {
    if (obj->leftHeapCount > obj->rightHeapCount) {
        return obj->leftHeap[0];
    } else if (obj->rightHeapCount > obj->leftHeapCount) {
        return obj->rightHeap[0];
    }
    
    return ((obj->leftHeap[0] + obj->rightHeap[0]) / 2.0);
}

void medianFinderFree(MedianFinder* obj) {
    free(obj->leftHeap);
    free(obj->rightHeap);
    free(obj);
}

/**
 * Your MedianFinder struct will be instantiated and called as such:
 * MedianFinder* obj = medianFinderCreate();
 * medianFinderAddNum(obj, num);
 
 * double param_2 = medianFinderFindMedian(obj);
 
 * medianFinderFree(obj);
*/