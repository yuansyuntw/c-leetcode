/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     struct ListNode *next;
 * };
 */


void reorderList(struct ListNode* head){
    struct ListNode *node1 = head->next;
    if (node1 == NULL) return;
    
    struct ListNode *node2 = node1->next;
    if (node2 == NULL) return;
    
    while(node2->next != NULL) {
        node1 = node2;
        node2 = node2->next;
    }
    
    struct ListNode *nextNode = head->next;
    head->next = node2;
    node2->next = nextNode;
    node1->next = NULL;
    
    reorderList(nextNode);
}