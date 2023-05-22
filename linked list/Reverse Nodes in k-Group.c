int numberOfList(struct ListNode *head)
{
    int count = 0;
    struct ListNode *node = head;
    while (node != NULL)
    {
        count++;
        node = node->next;
    }
    return count;
}

/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     struct ListNode *next;
 * };
 */
struct ListNode *reverseKGroup(struct ListNode *head, int k)
{
    if (k == 1)
    {
        return head;
    }

    struct ListNode *result = head;
    struct ListNode *node = head;
    struct ListNode *front = NULL;
    struct ListNode *end = NULL;
    struct ListNode *previous = NULL;
    struct ListNode *next = NULL;
    struct ListNode *previousEnd = NULL;

    int n = numberOfList(head);

    int group = n / k;
    int max = k * group;
    for (int i = 0; i < max; i++)
    {
        bool shouldReverse = true;
        if ((i % k) == 0)
        {
            end = node;
            shouldReverse = false;
        }

        if ((i % k) == (k - 1))
        {
            front = node;
            if (result == head)
            {
                result = front;
            }
            if (previousEnd != NULL)
            {
                previousEnd->next = front;
            }
            end->next = NULL;
            previousEnd = end;
        }

        next = node->next;
        if (shouldReverse)
        {
            node->next = previous;
        }
        previous = node;
        node = next;
    }

    bool shouldConnectToRemaining = ((max < n) && (node != NULL) && (end != NULL)); // 5
    if (shouldConnectToRemaining)
    {
        end->next = node;
    }

    return result;
}