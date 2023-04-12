int square(int value)
{
    return value * value;
}

/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
int *sortedSquares(int *nums, int numsSize, int *returnSize)
{
    int left = 0;
    int right = numsSize - 1;

    int *result = (int *)calloc(numsSize, sizeof(int));
    int resultIndex = numsSize - 1;
    while (left <= right)
    {
        int leftSquare = square(nums[left]);
        int rightSquare = square(nums[right]);

        // Reverse the solution.
        // Find the biggest square number.
        if (leftSquare > rightSquare)
        {
            result[resultIndex--] = leftSquare;
            left++;
        }
        else
        {
            result[resultIndex--] = rightSquare;
            right--;
        }
    }

    *returnSize = numsSize;
    return result;
}