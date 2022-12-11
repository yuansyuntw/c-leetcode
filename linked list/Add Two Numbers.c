/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     struct ListNode *next;
 * };
 */
struct ListNode *
addTwoNumbers(struct ListNode *l1, struct ListNode *l2)
{
    struct ListNode *sum = (struct ListNode *)calloc(1, sizeof(struct ListNode));
    struct ListNode *sumHead = sum;
    int carryValue = 0;
    struct ListNode *node1 = l1;
    struct ListNode *node2 = l2;

    while (true)
    {
        int value1 = 0;
        if (node1 != NULL)
        {
            value1 = node1->val;
            node1 = node1->next;
        }

        int value2 = 0;
        if (node2 != NULL)
        {
            value2 = node2->val;
            node2 = node2->next;
        }

        int valSum = value1 + value2 + carryValue;
        carryValue = valSum / 10;
        sum->val = valSum % 10;

        bool isStop = ((node1 == NULL) && (node2 == NULL) && (carryValue == 0));
        if (isStop)
        {
            break;
        }

        sum->next = (struct ListNode *)calloc(1, sizeof(struct ListNode));
        sum = sum->next;
    }

    return sumHead;
}