typedef struct {
    int key;
} HeapNode;

typedef struct {
    HeapNode **nodeArray;
    int nodeSize;
    int maxSize;
} MinHeap;

typedef struct {
    int k;
    MinHeap *minHeap;
} KthLargest;

int getParentNodeIndex(int nodeIndex) {
    return floor(nodeIndex/2);
}

void swapNode(HeapNode **node1, HeapNode **node2) {
    HeapNode *temp = *node1;
    *node1 = *node2;
    *node2 = temp;
}

void decreaseKey(MinHeap *minHeap, int nodeIndex, int newKey) {
    if ((nodeIndex <= 1) || (nodeIndex > minHeap->nodeSize)) {
        return;
    }
    
    HeapNode *node = minHeap->nodeArray[nodeIndex];
    
    if (newKey > node->key) {
        return;
    }
    
    // update the key
    node->key = newKey;
    
    while (nodeIndex > 1) {
        int parentIndex = getParentNodeIndex(nodeIndex);
        node = minHeap->nodeArray[nodeIndex];
        HeapNode *parent = minHeap->nodeArray[parentIndex];
        
        if (parent->key <= node->key) {
            break;
        }
        
        swapNode(&minHeap->nodeArray[nodeIndex], &minHeap->nodeArray[parentIndex]);
        nodeIndex = parentIndex;
    }
}

void minHeapInsert(MinHeap *minHeap, int value) {
    HeapNode *newNode = malloc(sizeof(HeapNode) * 1);
    newNode->key = value;
    
    minHeap->nodeArray[++minHeap->nodeSize] = newNode;
    decreaseKey(minHeap, minHeap->nodeSize, value);
}

void heapify(MinHeap *minHeap, int nodeIndex) {
    if ((nodeIndex < 1) || (nodeIndex > minHeap->nodeSize)) {
        return;
    }
    
    int left = 2 * nodeIndex;
    int right = 2 * nodeIndex + 1;
    int minIndex = nodeIndex;
    
    if  ((left <= minHeap->nodeSize) && (minHeap->nodeArray[left]->key < minHeap->nodeArray[minIndex]->key)) {
        minIndex = left;
    }
    
    if ((right <= minHeap->nodeSize) && (minHeap->nodeArray[right]->key < minHeap->nodeArray[minIndex]->key)) {
        minIndex = right;
    }
    
    if (minIndex != nodeIndex) {
        swapNode(&minHeap->nodeArray[nodeIndex], &minHeap->nodeArray[minIndex]);
        
        // look down the child index
        heapify(minHeap, minIndex);
    }
}

HeapNode *extractMinNode(MinHeap *minHeap) {
    if (minHeap->nodeSize < 1) {
        return NULL;
    }
    
    HeapNode *minNode = minHeap->nodeArray[1];
    
    minHeap->nodeArray[1] = minHeap->nodeArray[minHeap->nodeSize];
    
    minHeap->nodeArray[minHeap->nodeSize--] = NULL;
    heapify(minHeap, 1);
    
    return minNode;
}

int minimun(MinHeap *minHeap) {
    if (minHeap->nodeSize == 0) {
        printf("ERROR: the heap is empty\n");
        return 0;
    }
    
    return minHeap->nodeArray[1]->key;
}

KthLargest* kthLargestCreate(int k, int* nums, int numsSize) {
    KthLargest *largestObject = malloc(sizeof(KthLargest) * 1);
    largestObject->k = k;
    
    MinHeap *minHeap = malloc(sizeof(MinHeap) * 1);
    largestObject->minHeap = minHeap;
    
    minHeap->nodeSize = 0;
    minHeap->maxSize = 20001;
    minHeap->nodeArray = malloc(sizeof(HeapNode *) * minHeap->maxSize);
    
    // build the min heap.
    for (int i=0; i<numsSize;i++) {
        minHeapInsert(minHeap, nums[i]);
        if (minHeap->nodeSize > k) {
            HeapNode *minNode = extractMinNode(minHeap);
            free(minNode);
        }
    }

    return largestObject;
}

int kthLargestAdd(KthLargest* obj, int val) {
    minHeapInsert(obj->minHeap, val);
    if (obj->minHeap->nodeSize > obj->k) {
        if (obj->minHeap->nodeSize > obj->k) {
            HeapNode *minNode = extractMinNode(obj->minHeap);
            free(minNode);
        }
    }
    
    return minimun(obj->minHeap);
}

void kthLargestFree(KthLargest* obj) {
    for (int i=1;i<=obj->minHeap->nodeSize;i++) {
        if (obj->minHeap->nodeArray[i] != NULL) {
            free(obj->minHeap->nodeArray[i]);
        }
    }
    
    free(obj->minHeap->nodeArray);
    free(obj->minHeap);
    free(obj);   
}

/**
 * Your KthLargest struct will be instantiated and called as such:
 * KthLargest* obj = kthLargestCreate(k, nums, numsSize);
 * int param_1 = kthLargestAdd(obj, val);
 
 * kthLargestFree(obj);
*/