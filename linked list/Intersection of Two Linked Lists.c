/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     struct ListNode *next;
 * };
 */

int count(struct ListNode *head) {
    int result = 0;
    while (head != NULL) {
        result++;
        head = head->next;
    }
    
    return result;
}

struct ListNode *_getIntersectionNode(int differentCount, struct ListNode *biggerHead, struct ListNode *smallerHead) {
    if ((biggerHead == NULL) || (smallerHead == NULL)) {
        return NULL;
    }
    
    for (int i=0; i<differentCount; i++) {
        biggerHead = biggerHead->next;
    }
    
    while (biggerHead != smallerHead) {
        if (biggerHead == NULL) {
            break;
        }
        
        biggerHead = biggerHead->next;
        smallerHead = smallerHead->next;
    }
    
    return biggerHead;
}

struct ListNode *getIntersectionNode(struct ListNode *headA, struct ListNode *headB) {
    int headACount = count(headA);
    int headBCount = count(headB);
    int differentCount = abs(headACount - headBCount);
    if (headACount > headBCount) {
        return _getIntersectionNode(differentCount, headA, headB);
    } else {
        return _getIntersectionNode(differentCount, headB, headA);
    }
    
    return NULL;
}