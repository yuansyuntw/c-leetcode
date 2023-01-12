int targetSize;

int resultSize;
int *resultColumnSize;
int **result;

const int pathSize = 32;

int gK;

int *copyPath(int *path, int itemCount)
{
    int *newPath = (int *)calloc(pathSize, sizeof(int));
    if (newPath == NULL)
    {
        return NULL;
    }

    memcpy(newPath, path, itemCount * sizeof(int));

    return newPath;
}

void backtracking(int start, int end, int length, int *path)
{
    bool isMatch = (length == gK);
    if (isMatch)
    {
        int *newPath = copyPath(path, length);
        result[resultSize] = newPath;
        resultColumnSize[resultSize] = length;
        resultSize++;
        return;
    }

    int newLength = length + 1;
    if (newLength > pathSize)
    {
        return;
    }

    for (int i = start; i <= end; i++)
    {
        path[newLength - 1] = i;
        backtracking(i + 1, end, newLength, path);
        if (resultSize >= targetSize)
        {
            break;
        }
    }
}

int cNK(int n, int k)
{
    if (n == k)
    {
        return 1;
    }

    long numerator = n;
    for (int i = n - 1; i > k; i--)
    {
        numerator *= i;
    }

    long denominator = n - k;
    for (int i = denominator - 1; i > 0; i--)
    {
        denominator *= i;
    }

    return (numerator / denominator);
}

/**
 * Return an array of arrays of size *returnSize.
 * The sizes of the arrays are returned as *returnColumnSizes array.
 * Note: Both returned array and *columnSizes array must be malloced, assume caller calls free().
 */
int **combine(int n, int k, int *returnSize, int **returnColumnSizes)
{
    targetSize = cNK(n, k);

    resultSize = 0;
    resultColumnSize = (int *)calloc(targetSize, sizeof(int));
    result = (int **)calloc(targetSize, sizeof(int *));

    gK = k;

    int *path = (int *)calloc(pathSize, sizeof(int));
    int pathLength = 0;
    backtracking(1, n, pathLength, path);
    free(path);

    *returnSize = resultSize;
    *returnColumnSizes = resultColumnSize;
    return result;
}