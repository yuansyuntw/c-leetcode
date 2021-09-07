/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     struct ListNode *next;
 * };
 */
void deleteNode(struct ListNode* node) { 
    while (node->next != NULL) {
        node->val = node->next->val;
        
        if (node->next->next == NULL) {
            break;
        }
        
        node = node->next;
    }
    
    struct ListNode* lastNode = node->next;
    node->next = NULL;
    free(lastNode);
}