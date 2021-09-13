/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     struct ListNode *next;
 * };
 */

struct ListNode* mergeTwoLists(struct ListNode* l1, struct ListNode* l2){
    if ((l1 == NULL) && (l2 != NULL)) {
        return l2;
    }
    
    if ((l1 != NULL) && (l2 == NULL)) {
        return l1;
    }
    
    if ((l1 == NULL) && (l2 == NULL)) {
        return NULL;
    }
    
    struct ListNode *head, *node;
    if (l1->val > l2->val) {
        head = l2;
        l2 = l2->next;
    } else {
        head = l1;
        l1 = l1->next;
    }
    
    node = head;
    while ((l1 != NULL) && (l2 != NULL)) {
        if (l1->val > l2->val) {
            node->next = l2;
            l2 = l2->next;
        } else {
            node->next = l1;
            l1 = l1->next;
        }
        
        node = node->next;
    }
    
    if (l1 != NULL) {
        node->next = l1;
    }
    
    if (l2 != NULL) {
        node->next = l2;
    }
    
    return head;
}