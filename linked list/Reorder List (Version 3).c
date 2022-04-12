/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     struct ListNode *next;
 * };
 */

struct ListNode* reverseList(struct ListNode* head) {
    struct ListNode *preNode = NULL;
    while(head->next != NULL) {
        struct ListNode* temp = head->next;
        head->next = preNode;
        preNode = head;
        head = temp;
    }
    
    head->next = preNode;
    return head;
}

void reorderList(struct ListNode* head){
    if (head->next == NULL) return;
    
    struct ListNode* slowNode = head;
    struct ListNode* fastNode = head->next;
    while ((fastNode != NULL) && (fastNode->next != NULL)) {
        slowNode = slowNode->next;
        fastNode = fastNode->next->next;
    }
    
    struct ListNode* middleNode = slowNode;
    struct ListNode* head2 = reverseList(middleNode->next);
    middleNode->next = NULL;

    while(head2 != NULL) {
        struct ListNode* temp1 = head->next;
        struct ListNode* temp2 = head2->next;
        head->next = head2;
        head2->next = temp1;
        head = temp1;
        head2 = temp2;
    }
}