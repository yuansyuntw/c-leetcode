int numSquares(int n)
{
    // The dp[n] is the answer.
    int *dp = (int *)calloc(n + 1, sizeof(int));

    int sequaresCount = 0;
    int *sequares = (int *)calloc(n, sizeof(int));

    for (int i = 1; i <= n; i++)
    {
        // Make the square number to one.
        int onlyOneIndex = i * i;
        if (onlyOneIndex > n)
        {
            break;
        }

        dp[onlyOneIndex] = 1;
        sequares[sequaresCount++] = onlyOneIndex;
    }

    for (int i = 1; i <= n; i++)
    {
        if (dp[i] == 1)
        {
            continue;
        }

        int minSquares = INT_MAX;
        for (int sequareIndex = 0; sequareIndex < sequaresCount; sequareIndex++)
        {
            int sequare = sequares[sequareIndex];
            if (sequare > i)
            {
                break;
            }

            int remainingNumber = (i - sequare);
            if ((remainingNumber >= 0) && (remainingNumber < i) && ((dp[remainingNumber] + 1) < minSquares))
            {
                minSquares = dp[remainingNumber] + 1;
            }
        }

        if (minSquares == INT_MAX)
        {
            printf("something wrong\n");
            minSquares = i;
        }

        dp[i] = minSquares;
    }

    int result = dp[n];
    free(dp);
    free(sequares);

    return result;
}
