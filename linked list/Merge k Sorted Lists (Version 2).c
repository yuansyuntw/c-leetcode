int compare(void *pointer1, void *pointer2) {
    return (*(struct ListNode **)pointer1)->val - (*(struct ListNode **)pointer2)->val;
}

/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     struct ListNode *next;
 * };
 */
struct ListNode* mergeKLists(struct ListNode** lists, int listsSize){
    struct ListNode** nonNullLists = malloc(sizeof(struct ListNode *) * listsSize);
    int nonNullListsSize = 0;
    for (int i=0; i<listsSize; i++) {
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
    
    qsort(lists, listsSize, sizeof(struct ListNode *), compare);

    struct ListNode *startNode = NULL;
    struct ListNode *currentNode = NULL;
    int minValue;
    int minListIndex = 0;
    while (listsSize > 1) {
        struct ListNode *minNode = lists[minListIndex];
        if (startNode == NULL) {
            startNode = minNode;
            currentNode = startNode;
        } else {
            currentNode->next = minNode;
            currentNode = currentNode->next;
        }
        
        // insert the next node.
        struct ListNode *nextNode = minNode->next;
        if (nextNode != NULL) {
            for (int i=1; i<listsSize; i++) {
                if (nextNode->val <= lists[i]->val) {
                    lists[i-1] = nextNode;
                    break;
                } else{
                    lists[i-1] = lists[i];
                }
                
                if (i == listsSize-1) {
                    lists[i] = nextNode;
                }
            }
        } else {
            for (int i=0; i<listsSize-1; i++) {
                lists[i] = lists[i+1];
            }
            
            listsSize = listsSize - 1;
        }
    }
    
    if (listsSize == 1) {
        currentNode->next = lists[0];
    }
    
    free(nonNullLists);
    
    return startNode;
}