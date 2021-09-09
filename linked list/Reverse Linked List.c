/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     struct ListNode *next;
 * };
 */


struct ListNode* reverseList(struct ListNode* head) {
    if (head == NULL) {
        return head;
    }
    
    struct ListNode *node, *nextNode, *tempNode;
    
    node = head;
    nextNode = node->next;
    node->next = NULL;
    
    while (nextNode != NULL) {
        tempNode = nextNode->next;
        nextNode->next = node;
        node = nextNode;
        nextNode = tempNode;
    }
    
    head = node;
    
    return head;
}