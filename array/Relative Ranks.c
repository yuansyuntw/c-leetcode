typedef struct {
    int key;
    int scoreIndex;
} HeapNode;

typedef struct {
    HeapNode **nodeArray;
    int nodeSize;
    int maxSize;
} MaxHeap;

int getParentNodeIndex(int nodeIndex) {
    return floor(nodeIndex/2);
}

void swapNode(HeapNode **node1, HeapNode **node2) {
    HeapNode *temp = *node1;
    *node1 = *node2;
    *node2 = temp;
}

void increaseKey(MaxHeap *maxHeap, int nodeIndex, int newKey) {
    if ((nodeIndex < 1) || (nodeIndex > maxHeap->nodeSize)) {
        return;
    }
    
    HeapNode *node = maxHeap->nodeArray[nodeIndex];
    
    if (newKey < node->key) {
        return;
    }
    
    // update the key
    node->key = newKey;
    
    while (nodeIndex > 1) {
        int parentIndex = getParentNodeIndex(nodeIndex);
        int siblingIndex;
        if ((parentIndex%2) == 0) {
            siblingIndex = parentIndex + 1;
        } else {
            siblingIndex = parentIndex - 1;
        }
        
        if ((siblingIndex > 1) && (siblingIndex <= maxHeap->nodeSize)) {
            if (maxHeap->nodeArray[siblingIndex]->key < maxHeap->nodeArray[parentIndex]->key) {
                parentIndex = siblingIndex;
            }
        }
        
        node = maxHeap->nodeArray[nodeIndex];
        HeapNode *parent = maxHeap->nodeArray[parentIndex];
        
        if (parent->key >= node->key) {
            break;
        }
        
        swapNode(&maxHeap->nodeArray[nodeIndex], &maxHeap->nodeArray[parentIndex]);
        nodeIndex = parentIndex;
    }
}

void heapify(MaxHeap *maxHeap, int nodeIndex) {
    if ((nodeIndex < 1) || (nodeIndex > maxHeap->nodeSize)) {
        return;
    }
    
    int left = 2 * nodeIndex;
    int right = 2 * nodeIndex + 1;
    int maxIndex = nodeIndex;

    if  ((left <= maxHeap->nodeSize) && (maxHeap->nodeArray[left]->key > maxHeap->nodeArray[maxIndex]->key)) {
        maxIndex = left;
    }
    
    if ((right <= maxHeap->nodeSize) && (maxHeap->nodeArray[right]->key > maxHeap->nodeArray[maxIndex]->key)) {
        maxIndex = right;
    }
    
    if (maxIndex != nodeIndex) {
        swapNode(&maxHeap->nodeArray[nodeIndex], &maxHeap->nodeArray[maxIndex]);
        
        // look down the child index
        heapify(maxHeap, maxIndex);
    }
}

HeapNode *extractMaxNode(MaxHeap *maxHeap) {
    if (maxHeap->nodeSize < 1) {
        return NULL;
    }
    
    HeapNode *maxNode = maxHeap->nodeArray[1];
    maxHeap->nodeArray[1] = maxHeap->nodeArray[maxHeap->nodeSize];

    maxHeap->nodeArray[maxHeap->nodeSize--] = NULL;
    heapify(maxHeap, 1);
    
    return maxNode;
}


/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
char ** findRelativeRanks(int* score, int scoreSize, int* returnSize){
    MaxHeap *maxHeap = malloc(sizeof(MaxHeap));
    maxHeap->nodeArray = malloc(sizeof(HeapNode *) * (scoreSize + 1));
    maxHeap->nodeSize = 0;
    for (int i=0; i<scoreSize; i++) {
        maxHeap->nodeArray[++maxHeap->nodeSize] = malloc(sizeof(HeapNode));
        maxHeap->nodeArray[maxHeap->nodeSize]->key = score[i];
        maxHeap->nodeArray[maxHeap->nodeSize]->scoreIndex = i;
    }
    
    for (int i=floor(maxHeap->nodeSize); i>=1; i--) {
        heapify(maxHeap, i);
    }
    
    char **result = malloc(sizeof(char *) * scoreSize);
    *returnSize = scoreSize;
    
    for (int i=0; i<scoreSize; i++) {
        HeapNode *maxKeyNode = extractMaxNode(maxHeap);
        if (maxKeyNode == NULL) break;
        
        char *string = malloc(sizeof(char) * 32);
        switch (i) {
            case 0: {
                sprintf(string, "Gold Medal");
                break;
            }
            case 1: {
                sprintf(string, "Silver Medal");
                break;
            }
            case 2: {
                sprintf(string, "Bronze Medal");
                break;
            }
            default: {
                sprintf(string, "%d", i+1);
                break;
            }
        }
        
        result[maxKeyNode->scoreIndex] = string;
        free(maxKeyNode);
    }

    free(maxHeap->nodeArray);
    free(maxHeap);
    
    return result;
}