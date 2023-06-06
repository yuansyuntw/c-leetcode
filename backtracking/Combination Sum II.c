int gTarget;

int *gCandidates;
int gCandidatesSize;

int resultSize;
int **result;
int *resultSizes;
int resultCount;

void reallocResultSizeIfNeeded()
{
    if (resultCount <= (resultSize - 1))
    {
        return;
    }
    resultSize = resultSize * 2;
    result = (int **)realloc(result, resultSize * sizeof(int *));
    resultSizes = (int *)realloc(resultSizes, resultSize * sizeof(int));
}

int *copyArray(int *queue, int size)
{
    int *new = (int *)calloc(size, sizeof(int));
    for (int i = 0; i < size; i++)
    {
        new[i] = queue[i];
    }
    return new;
}

void backtracking(int index, int *queue, int size, int sum)
{
    if (sum == gTarget)
    {
        int *new = copyArray(queue, size);
        reallocResultSizeIfNeeded();
        result[resultCount] = new;
        resultSizes[resultCount] = size;
        resultCount++;
        return;
    }

    if ((sum > gTarget) || (index >= gCandidatesSize))
    {
        return;
    }

    int newIndex = index + 1;
    while ((newIndex < gCandidatesSize) && (gCandidates[newIndex] == gCandidates[index]))
    {
        newIndex++;
    }
    backtracking(newIndex, queue, size, sum);

    int value = gCandidates[index];
    queue[size] = value;
    int newSize = size + 1;
    int newSum = sum + value;
    backtracking(index + 1, queue, newSize, newSum);
}

int qsortCmp(void *left, void *right)
{
    int leftValue = *(int *)left;
    int rightValue = *(int *)right;
    return leftValue - rightValue;
}

/**
 * Return an array of arrays of size *returnSize.
 * The sizes of the arrays are returned as *returnColumnSizes array.
 * Note: Both returned array and *columnSizes array must be malloced, assume caller calls free().
 */
int **combinationSum2(int *candidates, int candidatesSize, int target, int *returnSize, int **returnColumnSizes)
{
    gTarget = target;

    qsort(candidates, candidatesSize, sizeof(int), qsortCmp);

    gCandidates = candidates;
    gCandidatesSize = candidatesSize;

    resultSize = candidatesSize;
    result = (int **)calloc(resultSize, sizeof(int *));
    resultSizes = (int *)calloc(resultSize, sizeof(int));
    resultCount = 0;

    int *queue = (int *)calloc(candidatesSize, sizeof(int));
    backtracking(0, queue, 0, 0);
    free(queue);

    *returnColumnSizes = resultSizes;
    *returnSize = resultCount;
    return result;
}
