
int *gNums;
int gNumsSize;

int **result;
int *colSizes;
int resultSize;

int *copySubset(int *subset, int size)
{
    int *newSubset = (int *)calloc(size, sizeof(int));
    memcpy(newSubset, subset, size * sizeof(int));
    return newSubset;
}

void backtracking(int currentIndex, int *subset, int length)
{
    if (currentIndex >= gNumsSize)
    {
        result[resultSize] = copySubset(subset, gNumsSize);
        colSizes[resultSize] = length;
        resultSize++;
        return;
    }

    int currentNumber = gNums[currentIndex];
    subset[length] = currentNumber;
    backtracking(currentIndex + 1, subset, length + 1);

    backtracking(currentIndex + 1, subset, length);
}

/**
 * Return an array of arrays of size *returnSize.
 * The sizes of the arrays are returned as *returnColumnSizes array.
 * Note: Both returned array and *columnSizes array must be malloced, assume caller calls free().
 */
int **subsets(int *nums, int numsSize, int *returnSize, int **returnColumnSizes)
{
    gNums = nums;
    gNumsSize = numsSize;

    int maxResultSize = pow(2, numsSize);
    int maxColSize = numsSize;

    resultSize = 0;
    result = (int **)calloc(maxResultSize, sizeof(int *));
    colSizes = (int *)calloc(maxResultSize, sizeof(int));

    int *subset = (int *)calloc(maxColSize, sizeof(int));
    backtracking(0, subset, 0);
    free(subset);

    *returnSize = resultSize;
    *returnColumnSizes = colSizes;

    return result;
}
