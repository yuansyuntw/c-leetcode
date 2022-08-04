struct Item {
    int node;
    int currentTime;
};

void swap(struct Item** heap, int index1, int index2) {
    struct Item* temp = heap[index1];
    heap[index1] = heap[index2];
    heap[index2] = temp;
}

int getParentIndex(int index) {
    return (index - 1)/ 2;
}

bool isSmallerChild(struct Item** heap, int index, int parentIndex) {
    return (heap[index]->currentTime < heap[parentIndex]->currentTime);
}

bool isNotRoot(int index) {
    return (index >= 1);
}

int decreaseKey(struct Item** heap, int heapCount, int index, int newTimes) {
    if ((index < 0) || (index >= heapCount)) {
        return INT_MAX;
    }

    bool isSmaller = (newTimes <= heap[index]->currentTime);
    if (isSmaller) {
        heap[index]->currentTime = newTimes;
        int parentIndex = getParentIndex(index);
        while (isNotRoot(index) && isSmallerChild(heap, index, parentIndex)) {
            swap(heap, index, parentIndex);
            index = parentIndex;
            parentIndex = getParentIndex(index);
        }
    }

    return heap[index]->currentTime;
}

int minHeapInsert(struct Item** heap, int heapSize, struct Item* item, int heapCount) {
    if ((heapCount + 1) >= heapSize) {
        // printf("Out of space for heap\n");
        return heapCount;
    }

    int insertedIndex = heapCount;
    heap[heapCount++] = item;
    decreaseKey(heap, heapCount, insertedIndex, item->currentTime);

    return heapCount;
}

int minHeapInsertOrDecreaseKey(struct Item** heap, int heapSize, int* heapCount, int node, int time) {
    int index = -1;
    for (int i = 0; i < (*heapCount); i++) {
        if (heap[i]->node == node) {
            index = i;
            break;
        }
    }

    bool isExist = (index != -1);
    if (isExist) {
        bool isSmallerValue = time < heap[index]->currentTime;
        time = decreaseKey(heap, (*heapCount), index, time);
    }
    else {
        struct Item* item = (struct Item*)calloc(1, sizeof(struct Item));
        item->node = node;
        item->currentTime = time;
        (*heapCount) = minHeapInsert(heap, heapSize, item, (*heapCount));
    }

    return time;
}

int leftIndex(int index) {
    return (index * 2) + 1;
}

int rightIndex(int index) {
    return (index * 2) + 2;
}

void minHeapify(struct Item** heap, int index, int checkedIndex) {
    int left = leftIndex(index);
    int right = rightIndex(index);
    int smallest = index;

    bool isInRange = (left <= checkedIndex);
    if (isInRange) {
        bool isSmaller = (heap[left]->currentTime < heap[smallest]->currentTime);
        if (isSmaller) {
            smallest = left;
        }
    }

    isInRange = (right <= checkedIndex);
    if (isInRange) {
        bool isSmaller = (heap[right]->currentTime < heap[smallest]->currentTime);
        if (isInRange && isSmaller) {
            smallest = right;
        }
    }

    if (smallest != index) {
        swap(heap, smallest, index);
        minHeapify(heap, smallest, checkedIndex);
    }
}

struct Item* extractMin(struct Item** heap, int heapSize, int* heapCount) {
    if ((*heapCount) == 0) {
        return NULL;
    }

    int firstOneIndex = 0;
    struct Item* item = heap[firstOneIndex];

    int lastOneIndex = (*heapCount) - 1;
    heap[firstOneIndex] = heap[lastOneIndex];
    (*heapCount)--;
    minHeapify(heap, 0, (*heapCount));

    return item;
}

int networkDelayTime(int** times, int timesSize, int* timesColSize, int n, int k) {
    // two-dimention
    int** map = (int **)calloc(sizeof(int *), (n + 1));
    for (int u = 1; u <= n; u++) {
        map[u] = (int *)calloc(sizeof(int), (n + 1));
        for (int v = 1; v <= n; v++) {
            map[u][v] = -1;
        }
    }

    for (int i = 0; i < timesSize; i++) {
        int* connection = times[i];
        int u = connection[0];
        int v = connection[1];
        int w = connection[2];
        map[u][v] = w;
    }

    int seenCount = 0;
    int* seenNode = (int*)calloc(sizeof(int), (n + 1));
    seenNode[k] = 1;

    int heapSize = 6001;
    int heapCount = 0;
    struct Item** heap = (struct Item**)calloc(sizeof(struct Item*), heapSize);

    int maxTime = -1;
    int currentTime = 0;
    bool isFirstTime = true;
    while (true) {
        bool isNotToSkipForPop = !isFirstTime;
        isFirstTime = false;
        if (isNotToSkipForPop) {
            struct Item* topItem = extractMin(heap, heapSize, &heapCount);
            if (topItem == NULL) {
                maxTime = -1;
                break;
            }

            currentTime = topItem->currentTime;
            k = topItem->node;

            if (currentTime > maxTime) {
                maxTime = currentTime;
            }
        }

        for (int i = 1; i <= n; i++) {
            bool isConnectToOther = (map[k][i] != -1);
            if (isConnectToOther) {
                bool isNotSeen = (seenNode[i] == 0);
                if (isNotSeen) {
                    int node = i;
                    int time = currentTime + map[k][i];
                    int smallerTime = minHeapInsertOrDecreaseKey(heap, heapSize, &heapCount, node, time);
                }
            }
        }

        seenNode[k] = 1;
        seenCount++;
        bool isSeeAllNode = (seenCount == n);
        if (isSeeAllNode) {
            break;
        }
    }

    for (int i = 0; i < heapCount; i++) {
        free(heap[i]);
        if (i < n) {
            free(map[i]);
            if (i == n - 1) {
                free(map[i + 1]);
            }
        }
    }
    free(heap);
    free(map);
    free(seenNode);

    return maxTime;
}