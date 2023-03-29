// 1. sort the number array
// 2. recursive the k sum.
// 3. put the number into the `temp` array.
// 4. if the length of the `temp` array is 2, we apply the method of two sums II to fund the reset number.
// 5. if the length of the `temp` array is 4, we add it to the `result` array.

int qsortCmp(const void *lhs, const void *rhs)
{
    int *left = (int *)lhs;
    int *right = (int *)rhs;
    return (*left) - (*right);
}

int sumLength;

int *gNums;
int gNumsSize;

int **result;
int resultCount;
int *columnSize;

int *subResult;
int subResultCount;

void addToResult()
{
    if (subResultCount != sumLength)
    {
        printf("adding to result fail: sub result count is wrong\n");
        return;
    }
    memcpy(result[resultCount], subResult, sizeof(int) * subResultCount);
    columnSize[resultCount] = sumLength;
    resultCount++;
}

void kSum(int startIndex, long int target)
{
    if (subResultCount < 2)
    {
        for (int i = startIndex; i < (gNumsSize - 2); i++)
        {
            // Avoid duplicated result
            if ((i > startIndex) && (gNums[i] == gNums[i - 1]))
            {
                continue;
            }
            int currentNum = gNums[i];
            subResult[subResultCount++] = currentNum;
            long int newTarget = (long int)target - (long int)currentNum;
            kSum(i + 1, newTarget);
            subResultCount--;
        }
        return;
    }

    // Sum two base case
    int left = startIndex;
    int right = gNumsSize - 1;

    while (left < right)
    {
        long int sum = (long int)gNums[left] + (long int)gNums[right];
        if (sum == target)
        {
            subResult[subResultCount++] = gNums[left];
            subResult[subResultCount++] = gNums[right];
            addToResult();
            subResultCount -= 2;
            left++;
            while ((left < right) && (gNums[left] == gNums[left - 1]))
            {
                left++;
            }
        }
        else if (sum < target)
        {
            left++;
        }
        else if (sum > target)
        {
            right--;
        }
    }
}

/**
 * Return an array of arrays of size *returnSize.
 * The sizes of the arrays are returned as *returnColumnSizes array.
 * Note: Both returned array and *columnSizes array must be malloced, assume caller calls free().
 */
int **fourSum(int *nums, int numsSize, int target, int *returnSize, int **returnColumnSizes)
{
    qsort(nums, numsSize, sizeof(int), qsortCmp);
    gNums = nums;
    gNumsSize = numsSize;

    sumLength = 4;
    int resultSize = 200;
    result = (int **)calloc(resultSize, sizeof(int *));
    for (int i = 0; i < resultSize; i++)
    {
        result[i] = (int *)calloc(sumLength, sizeof(int));
    }
    columnSize = (int *)calloc(resultSize, sizeof(int));
    resultCount = 0;

    subResult = (int *)calloc(sumLength, sizeof(int));
    subResultCount = 0;

    kSum(0, target);

    *returnSize = resultCount;
    *returnColumnSizes = columnSize;
    return result;
}