int *gNums;
int gNumsSize;

void addQueue(int *queue, int *startIndex, int *endIndex, int targetIndex)
{
    int targetNumber = gNums[targetIndex];
    while (*startIndex <= *endIndex)
    {
        int index = queue[(*endIndex)];
        if (targetNumber >= gNums[index])
        {
            (*endIndex)--;
        }
        else
        {
            break;
        }
    }
    queue[(++(*endIndex))] = targetIndex;
}

/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
int *maxSlidingWindow(int *nums, int numsSize, int k, int *returnSize)
{
    gNums = nums;
    gNumsSize = numsSize;

    int queueEndIndex = -1;
    int queueStartIndex = 0;
    int *queue = (int *)calloc(numsSize, sizeof(int));

    int resultSize = numsSize - k + 1;
    int *result = (int *)calloc(resultSize, sizeof(int));
    int resultCount = 0;

    for (int i = 0; i < k; i++)
    {
        addQueue(queue, &queueStartIndex, &queueEndIndex, i);
    }
    int maxIndex = queue[queueStartIndex];
    result[resultCount++] = gNums[maxIndex];

    for (int i = 1; i < resultSize; i++)
    {
        int removedNumberIndex = i - 1;
        if (queue[queueStartIndex] == removedNumberIndex)
        {
            queueStartIndex++;
        }

        int addNumberIndex = i + k - 1;
        addQueue(queue, &queueStartIndex, &queueEndIndex, addNumberIndex);

        maxIndex = queue[queueStartIndex];
        result[resultCount++] = gNums[maxIndex];
    }

    free(queue);

    *returnSize = resultSize;
    return result;
}
