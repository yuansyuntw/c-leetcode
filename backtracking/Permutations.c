// 1. backtracking find the nums in each loop
// 2. prepare a wasSeen table, if the number was seen, we skip it.
// 3. if all the numbers are seen, we put them into the return list.
// 4. if all possibilities are seen, we return the return list.

int *gNums;
int gNumsSize;

int **result;
int *columns;
int resultCount;

int getPosibilityCount(int numsSize)
{
    int result = numsSize; // 3
    for (int i = numsSize - 1; i >= 1; i--)
    {
        result *= i; // 2 1
    }
    return result; // 6
}

void copyNumsAndRemoveItem(int *nums, int size, int index, int *newNums, int *newSize)
{
    int *copyNums = (int *)calloc(size, sizeof(int)); // 1
    memcpy(copyNums, nums, sizeof(int) * size);       // [3, 2]

    int last = size - 1;
    copyNums[index] = copyNums[last]; // replace the index item with last item. // [3, 2]

    *newSize = size - 1;
    *newNums = copyNums; // [3]
}

void putResult(int *tempList, int tempCount)
{
    for (int i = 0; (i < gNumsSize && i < tempCount); i++)
    {
        result[resultCount][i] = tempList[i];
    }
    columns[resultCount] = tempCount;
    resultCount++;
}

// dictionary
// array*
//

void backtracking(int *nums, int numsSize, int *tempList, int tempCount)
{
    if (tempCount == gNumsSize)
    {
        putResult(tempList, tempCount);
        return;
    }

    for (int i = 0; i < numsSize; i++)
    {                                    // 1
        tempList[tempCount++] = nums[i]; // 2
        int *newNums;
        int newNumsSize;
        copyNumsAndRemoveItem(nums, numsSize, i, newNums, &newNumsSize);
        backtracking(newNums, newNumsSize, tempList, tempCount);
        free(newNums);
        tempCount--;
    }
}

/**
 * Return an array of arrays of size *returnSize.
 * The sizes of the arrays are returned as *returnColumnSizes array.
 * Note: Both returned array and *columnSizes array must be malloced, assume caller calls free().
 */
int **permute(int *nums, int numsSize, int *returnSize, int **returnColumnSizes)
{
    gNums = nums;
    gNumsSize = numsSize;

    int posibilityCount = getPosibilityCount(gNumsSize); // 6
    result = (int **)calloc(posibilityCount, sizeof(int *));
    for (int i = 0; i < posibilityCount; i++)
    {
        result[i] = (int *)calloc(gNumsSize, sizeof(int));
    }
    columns = (int *)calloc(posibilityCount, sizeof(int));
    resultCount = 0;

    int *tempList = (int *)calloc(gNumsSize, sizeof(int));
    bracktracking(0, tempList, 0);
    free(tempList);

    *returnSize = resultCount;
    *returnColumnSizes = columns;
    return result;
}
