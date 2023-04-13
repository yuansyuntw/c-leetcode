// 1. Start from the right-bottom corner
// 2. Set each cell with the mini cost from right to left.
// 3. Go to the previous row and do step 2 until the first row

int getValue(int **dp, int rowSize, int colSize, int r, int c)
{
    if ((r < rowSize) && (r >= 0) && (c < colSize) && (c >= 0))
    {
        return dp[r][c];
    }

    return INT_MAX;
}

int minPathSum(int **grid, int gridSize, int *gridColSize)
{
    int **dp = (int **)calloc(gridSize, sizeof(int *));
    for (int i = 0; i < gridSize; i++)
    {
        dp[i] = (int *)calloc(gridColSize[i], sizeof(int));
    }

    for (int row = gridSize - 1; row >= 0; row--)
    {
        int colSize = gridColSize[row];
        for (int col = colSize - 1; col >= 0; col--)
        {
            if ((row == gridSize - 1) && (col == colSize - 1))
            {
                // right-bottom cell
                dp[row][col] = grid[row][col];
                continue;
            }

            int bottomValue = getValue(dp, gridSize, colSize, row + 1, col);
            int rightValue = getValue(dp, gridSize, colSize, row, col + 1);
            int minValue = rightValue;
            if (bottomValue < rightValue)
            {
                minValue = bottomValue;
            }
            dp[row][col] = grid[row][col] + minValue;
        }
    }

    int result = dp[0][0];
    for (int i = 0; i < gridSize; i++)
    {
        free(dp[i]);
    }
    free(dp);

    return result;
}
