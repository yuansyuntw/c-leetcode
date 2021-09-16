/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     struct ListNode *next;
 * };
 */
bool isPalindrome(struct ListNode* head){
    if (head->next == NULL) {
        return true;
    }
    
    struct ListNode *centerNode;
    struct ListNode *fastNode = head;
    struct ListNode *slowNode = head;
    while ((fastNode != NULL) && (fastNode->next != NULL)) {
        fastNode = fastNode->next->next;
        slowNode = slowNode->next;
    }
    
    centerNode = slowNode;

    // Reverse the half of trail nodes
    struct ListNode *node = centerNode;
    struct ListNode *nextNode = NULL;
    struct ListNode *previousNode = NULL;
    while (node != NULL) {
        nextNode = node->next;
        node->next = previousNode;

        previousNode = node;
        node = nextNode;
    }

    struct ListNode *tailHead = previousNode;

    // Compare front and tail node.
    bool isSame = true;
    while ((head != NULL) && (tailHead != NULL)) {
        if (head->val != tailHead->val) {
            isSame = false;
            break;
        }
        
        head = head->next;
        tailHead = tailHead->next;
    }
    
    return isSame;
}