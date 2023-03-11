struct ListNode *findPreviousMiddle(struct ListNode *head)
{
    struct ListNode *start = head;
    struct ListNode *previous = head;
    struct ListNode *slower = head;
    struct ListNode *faster = head;
    while (faster->next != NULL)
    {
        if (slower == NULL)
        {
            return NULL;
        }

        previous = slower;
        slower = slower->next;

        if (faster->next->next == NULL)
        {
            break;
        }
        faster = faster->next->next;
    }

    return previous;
}

void swapVal(struct ListNode *left, struct ListNode *right)
{
    int temp = left->val;
    left->val = right->val;
    right->val = temp;
}

void printList(struct ListNode *head)
{
    while (head != NULL)
    {
        printf("%d ", head->val);
        head = head->next;
    }
}

struct ListNode *mergeSort(struct ListNode *head)
{
    struct ListNode *previousMiddle = findPreviousMiddle(head);
    if (previousMiddle == NULL)
    {
        return head;
    }

    // This list is only one number.
    if (previousMiddle->next == NULL)
    {
        return head;
    }

    struct ListNode *middle = previousMiddle->next;
    struct ListNode *leftGroup = head;
    struct ListNode *rightGroup = middle;

    // Base case
    if ((leftGroup->next == rightGroup) && (rightGroup->next == NULL))
    {
        // swap
        if (leftGroup->val > rightGroup->val)
        {
            swapVal(leftGroup, rightGroup);
        }
        return leftGroup;
    }

    // merge sort
    previousMiddle->next = NULL;
    leftGroup = mergeSort(leftGroup);
    rightGroup = mergeSort(rightGroup);

    struct ListNode *current = NULL;
    struct ListNode *result = NULL;
    if (leftGroup->val < rightGroup->val)
    {
        result = leftGroup;
        current = leftGroup;
        leftGroup = leftGroup->next;
    }
    else
    {
        result = rightGroup;
        current = rightGroup;
        rightGroup = rightGroup->next;
    }

    while ((leftGroup != NULL) && (rightGroup != NULL))
    {
        if (leftGroup->val < rightGroup->val)
        {
            current->next = leftGroup;
            leftGroup = leftGroup->next;
        }
        else
        {
            current->next = rightGroup;
            rightGroup = rightGroup->next;
        }
        current = current->next;
    }

    if (leftGroup != NULL)
    {
        current->next = leftGroup;
    }
    else if (rightGroup != NULL)
    {
        current->next = rightGroup;
    }

    return result;
}

/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     struct ListNode *next;
 * };
 */
struct ListNode *sortList(struct ListNode *head)
{
    if (head == NULL)
    {
        return NULL;
    }
    return mergeSort(head);
}
