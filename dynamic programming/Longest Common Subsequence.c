int max(int left, int right)
{
    if (left > right)
    {
        return left;
    }
    else
    {
        return right;
    }
}

int longestCommonSubsequence(char *text1, char *text2)
{
    int text1Length = strlen(text1);
    int text2Length = strlen(text2);

    int colSize = text2Length + 1;
    int rowSize = text1Length + 1;
    int **dp = (int **)calloc(colSize, sizeof(int *));
    for (int i = 0; i < colSize; i++)
    {
        dp[i] = (int *)calloc(rowSize, sizeof(int));
    }

    for (int row = text2Length - 1; row >= 0; row--)
    {
        for (int col = text1Length - 1; col >= 0; col--)
        {
            if (text1[col] == text2[row])
            {
                // These texts have the same char, we remove it on both texts.
                dp[row][col] = dp[row + 1][col + 1] + 1;
            }
            else
            {
                // Remove the char from one of the texts, and get the result by the max value.
                dp[row][col] = max(dp[row + 1][col], dp[row][col + 1]);
            }
        }
    }

    int maxLength = dp[0][0];

    for (int i = 0; i < colSize; i++)
    {
        free(dp[i]);
    }
    free(dp);

    return maxLength;
}
