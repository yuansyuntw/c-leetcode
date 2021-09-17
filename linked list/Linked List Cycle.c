/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     struct ListNode *next;
 * };
 */
bool hasCycle(struct ListNode *head) {
    bool isHasCycle = false;
    
    struct ListNode *fastNode = head;
    struct ListNode *slowNode = head;
    while ((fastNode != NULL) && (fastNode->next != NULL)) {
        fastNode = fastNode->next->next;
        slowNode = slowNode->next;
        if (slowNode == fastNode) {
            isHasCycle = true;
            break;
        }
    }
    
    return isHasCycle;
}