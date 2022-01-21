/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     struct ListNode *next;
 * };
 */

struct HeapNode {
    int listsIndex;
    int key;
};

struct MinHeap {
    int nodeSize;
    struct HeapNode **nodeArray;
};

int getParentNodeIndex(int nodeIndex) {
    return floor(nodeIndex/2);
}

void swapNode(struct HeapNode **node1, struct HeapNode **node2) {
    struct HeapNode *temp = *node1;
    *node1 = *node2;
    *node2 = temp;
}

void decreaseKey(struct MinHeap *minHeap, int nodeIndex, int newKey) {
    if ((nodeIndex <= 1) || (nodeIndex > minHeap->nodeSize)) {
        return;
    }

    struct HeapNode *node = minHeap->nodeArray[nodeIndex];
    if (newKey > node->key) {
        return;
    }
    
    // update the key
    node->key = newKey;
    
    while (nodeIndex > 1) {
        int parentIndex = getParentNodeIndex(nodeIndex);
        node = minHeap->nodeArray[nodeIndex];
        struct HeapNode *parent = minHeap->nodeArray[parentIndex];
        if (parent->key <= node->key) {
            break;
        }

        swapNode(&minHeap->nodeArray[nodeIndex], &minHeap->nodeArray[parentIndex]);
        nodeIndex = parentIndex;
    }
}

void minHeapInsert(struct MinHeap *minHeap, int value, int listsIndex) {
    struct HeapNode *newNode = malloc(sizeof(struct HeapNode) * 1);
    newNode->key = value;
    newNode->listsIndex = listsIndex;

    minHeap->nodeArray[++minHeap->nodeSize] = newNode;
    decreaseKey(minHeap, minHeap->nodeSize, value);
}

void heapify(struct MinHeap *minHeap, int nodeIndex) {
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

struct HeapNode *extractMinNode(struct MinHeap *minHeap) {
    if (minHeap->nodeSize < 1) {
        return NULL;
    }
    
    struct HeapNode *minNode = minHeap->nodeArray[1];
    minHeap->nodeArray[1] = minHeap->nodeArray[minHeap->nodeSize];
    minHeap->nodeArray[minHeap->nodeSize--] = NULL;
    heapify(minHeap, 1);
    
    return minNode;
}

struct ListNode* mergeKLists(struct ListNode** lists, int listsSize){
    struct ListNode **nonNullLists = malloc(sizeof(struct ListNode *) * listsSize);
    int nonNullListsSize = 0;
    for (int i=0;i<listsSize;i++) {
        if (lists[i] != NULL) {
            nonNullLists[nonNullListsSize++] = lists[i];
        }
    }
    
    lists = nonNullLists;
    listsSize = nonNullListsSize;
    
    if (listsSize == 0) {
        return NULL;
    }
    
    if (listsSize == 1) {
        return lists[0];
    }
    
    struct MinHeap *minHeap = malloc(sizeof(struct MinHeap));
    minHeap->nodeSize = 0;
    minHeap->nodeArray = malloc(sizeof(struct HeapNode *) * (listsSize + 1));
    for (int i=0; i<listsSize; i++) {
        minHeap->nodeArray[i+1] = malloc(sizeof(struct HeapNode));
        minHeap->nodeArray[i+1]->listsIndex = i;
        minHeap->nodeArray[i+1]->key = lists[i]->val;
        minHeap->nodeSize++;
    }
    
    for (int i=floor(minHeap->nodeSize/2); i>=1; i--) {
        heapify(minHeap, i);
    }
    
    struct ListNode *startNode = NULL;
    struct ListNode *currentNode = NULL;
    int minValue = 9999;
    int minListIndex = 0;
    while (listsSize > 1) {
        struct HeapNode *minHeapNode = extractMinNode(minHeap);
        
        if (minHeapNode == NULL) {
            break;
        }
        
        minValue = minHeapNode->key;
        minListIndex = minHeapNode->listsIndex;
        free(minHeapNode);
        
        struct ListNode *minNode = lists[minListIndex];
        if (startNode == NULL) {
            startNode = minNode;
            currentNode = startNode;
        } else {
            currentNode->next = minNode;
            currentNode = currentNode->next;
        }
        
        // move the head to next one. 
        lists[minListIndex] = lists[minListIndex]->next;
        if (lists[minListIndex] != NULL) {
            minHeapInsert(minHeap, lists[minListIndex]->val, minListIndex);
        } else {
            listsSize--;
        }
    }
    
    if (listsSize == 1) {
        struct HeapNode *minHeapNode = extractMinNode(minHeap);
        currentNode->next = lists[minHeapNode->listsIndex];
        free(minHeapNode);
    }
    
    for (int i=1;i<=minHeap->nodeSize;i++) {
        free(minHeap->nodeArray[i]);
    }
    
    free(minHeap);
    free(nonNullLists);
    
    return startNode;
}