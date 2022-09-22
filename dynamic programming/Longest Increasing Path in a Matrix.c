int max(int valueA, int valueB)
{
    if (valueA > valueB)
    {
        return valueA;
    }

    return valueB;
}

int getPathLength(int **matrix, int matrixSize, int matrixColSize, int **dp, int row, int col, int currentValue)
{
    if ((row < 0) || (row >= matrixSize) || (col < 0) || (col >= matrixColSize))
    {
        return 0;
    }

    bool canNotAccess = (currentValue >= matrix[row][col]);
    if (canNotAccess)
    {
        return 0;
    }

    bool hasSeen = (dp[row][col] != 0);
    if (hasSeen)
    {
        return dp[row][col];
    }

    int currentPathLength = 0;

    int newCurrentValue = matrix[row][col];
    currentPathLength = max(currentPathLength, getPathLength(matrix, matrixSize, matrixColSize, dp, row - 1, col, newCurrentValue));
    currentPathLength = max(currentPathLength, getPathLength(matrix, matrixSize, matrixColSize, dp, row + 1, col, newCurrentValue));
    currentPathLength = max(currentPathLength, getPathLength(matrix, matrixSize, matrixColSize, dp, row, col - 1, newCurrentValue));
    currentPathLength = max(currentPathLength, getPathLength(matrix, matrixSize, matrixColSize, dp, row, col + 1, newCurrentValue));

    currentPathLength += 1;

    dp[row][col] = currentPathLength;

    return currentPathLength;
}

int longestIncreasingPath(int **matrix, int matrixSize, int *matrixColSize)
{
    int **dp = (int **)calloc(matrixSize, sizeof(int *));
    int colSize = matrixColSize[0];
    for (int r = 0; r < matrixSize; r++)
    {
        dp[r] = (int *)calloc(colSize, sizeof(int));
    }

    int maxPathLength = 0;
    bool isStop = false;
    for (int r = 0; r < matrixSize; r++)
    {
        for (int c = 0; c < colSize; c++)
        {
            bool hasSeen = (dp[r][c] != 0);
            if (hasSeen)
            {
                continue;
            }

            int newPathLength = getPathLength(matrix, matrixSize, colSize, dp, r, c, -1);
            if (newPathLength > maxPathLength)
            {
                maxPathLength = newPathLength;

                isStop = (maxPathLength == (matrixSize * colSize));
            }

            if (isStop)
            {
                break;
            }
        }

        if (isStop)
        {
            break;
        }
    }

    for (int r = 0; r < matrixSize; r++)
    {
        free(dp[r]);
    }
    free(dp);

    return maxPathLength;
}