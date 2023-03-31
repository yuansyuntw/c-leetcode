// 1. start from the last one to the first.
// 2. put the value and the index into the stack
// 3. if the value is bigger than the value of the top of the stack, we replace it.
// 4. find the distance between the top and the previous.
// 5. set the distance into the answer list.

struct Item
{
    int index;
    int value;
};

struct Item **stack;
int stackCount;

int pushStackAndReturnDistance(int value, int index)
{
    for (int i = stackCount - 1; i >= 0; i--)
    {
        struct Item *item = stack[i];
        if (item->value <= value)
        {
            free(item);
            stackCount--;
        }
        else
        {
            break;
        }
    }

    struct Item *newItem = (struct Item *)calloc(1, sizeof(struct Item));
    newItem->value = value;
    newItem->index = index;
    stack[stackCount++] = newItem;

    int distance = 0;
    if (stackCount >= 2)
    {
        struct Item *previousItem = stack[stackCount - 2];
        distance = previousItem->index - index;
    }
    return distance;
}

/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
int *dailyTemperatures(int *temperatures, int temperaturesSize, int *returnSize)
{
    stack = (struct Item **)calloc(temperaturesSize, sizeof(struct Item *));
    stackCount = 0;

    int *answers = (int *)calloc(temperaturesSize, sizeof(int));
    for (int i = temperaturesSize - 1; i >= 0; i--)
    {
        int value = temperatures[i];
        int index = i;
        answers[i] = pushStackAndReturnDistance(value, index);
    }

    for (int i = 0; i < stackCount; i++)
    {
        free(stack[i]);
    }
    free(stack);

    *returnSize = temperaturesSize;
    return answers;
}
