/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     struct ListNode *next;
 * };
 */


struct ListNode* removeNthFromEnd(struct ListNode* head, int n){
    struct ListNode *node, *targetNode, *previousTargetNode;
    
    node = head;
    
    if ((node->next == NULL) && (n == 1)) {
        head = NULL;
        free(node);
        return head;
    }
    
    targetNode = head;
    previousTargetNode = NULL;
    
    int travelCount = 1;
    while(node->next != NULL) {
        if (travelCount >= n) {
            if (targetNode->next != NULL) {
                previousTargetNode = targetNode;
                targetNode = targetNode->next;
            }
        } 
        
        node = node->next;
        travelCount++;
    }
    
    if (previousTargetNode == NULL) {
        head = targetNode -> next;
    } else {
        previousTargetNode->next = targetNode->next;
    }
    
    free(targetNode);
    
    return head;
}