/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     struct ListNode *next;
 * };
 */


void reorderList(struct ListNode* head){
    struct ListNode** stack = malloc(sizeof(struct ListNode *) * 50000);
    int frontIndex = 0;
    int rearIndex = -1;
    
    struct ListNode* node = head;
    while(node != NULL) {
        stack[++rearIndex] = node;
        node = node->next;
    }
    
    while(rearIndex > frontIndex) {
        stack[frontIndex++]->next = stack[rearIndex];
        if (frontIndex == rearIndex) break;
        stack[rearIndex--]->next = stack[frontIndex];
    }
    
    stack[rearIndex]->next = NULL;
    
    free(stack);
}