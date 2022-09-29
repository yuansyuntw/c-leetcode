int max(int valueA, int valueB)
{
    if (valueA > valueB)
    {
        return valueA;
    }

    return valueB;
}

int getMoneyAmount(int n)
{
    int dpSize = n + 2;
    int **dp = calloc(dpSize, sizeof(int *));
    for (int i = 0; i < dpSize; i++)
    {
        dp[i] = calloc(dpSize, sizeof(int));
    }

    for (int length = 2; length <= n; length++)
    {
        int maxStart = n - length + 1;
        for (int start = 1; start <= maxStart; start++)
        {
            int minMoney = INT_MAX;
            int end = start + length - 1;
            for (int pivot = start; pivot <= end; pivot++)
            {
                int money = pivot + max(dp[start][pivot - 1], dp[pivot + 1][end]);
                if (money < minMoney)
                {
                    minMoney = money;
                }
            }

            dp[start][end] = minMoney;
        }
    }

    int result = dp[1][n];

    for (int i = 0; i < dpSize; i++)
    {
        free(dp[i]);
    }
    free(dp);

    return result;
}