int smallestIndex;
int biggestIndex;

void minIndex(int *nums, int startIndex, int endIndex, int target)
{
    if ((endIndex - startIndex + 1) <= 2)
    {
        if (nums[endIndex] == target)
        {
            smallestIndex = endIndex;
        }

        if (nums[startIndex] == target)
        {
            smallestIndex = startIndex;
        }

        return;
    }

    int middleIndex = (startIndex + endIndex) / 2;
    if (nums[middleIndex] == target)
    {
        smallestIndex = middleIndex;
    }

    if (nums[middleIndex] >= target)
    {
        minIndex(nums, startIndex, middleIndex, target);
    }
    else
    {
        minIndex(nums, middleIndex, endIndex, target);
    }
}

void maxIndex(int *nums, int startIndex, int endIndex, int target)
{
    if ((endIndex - startIndex + 1) <= 2)
    {
        if (nums[startIndex] == target)
        {
            biggestIndex = startIndex;
        }

        if (nums[endIndex] == target)
        {
            biggestIndex = endIndex;
        }

        return;
    }

    int middleIndex = (startIndex + endIndex) / 2;
    if (nums[middleIndex] == target)
    {
        biggestIndex = middleIndex;
    }

    if (nums[middleIndex] <= target)
    {
        maxIndex(nums, middleIndex, endIndex, target);
    }
    else
    {
        maxIndex(nums, startIndex, middleIndex, target);
    }
}

/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
int *searchRange(int *nums, int numsSize, int target, int *returnSize)
{
    smallestIndex = -1;
    biggestIndex = -1;

    if (numsSize > 0)
    {
        minIndex(nums, 0, numsSize - 1, target);
        maxIndex(nums, 0, numsSize - 1, target);
    }

    int *result = (int *)calloc(2, sizeof(int));
    result[0] = smallestIndex;
    result[1] = biggestIndex;
    *returnSize = 2;
    
    return result;
}
