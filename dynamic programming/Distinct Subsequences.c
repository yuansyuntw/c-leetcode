int numDistinct(char *s, char *t)
{
    int sSize = strlen(s);
    int tSize = strlen(t);

    if (sSize < tSize)
    {
        return 0;
    }

    unsigned int **dp = (int **)calloc(tSize, sizeof(unsigned int *));
    for (int i = 0; i < tSize; i++)
    {
        dp[i] = (unsigned int *)calloc(sSize, sizeof(unsigned int));
    }

    for (int tIndex = tSize - 1; tIndex >= 0; tIndex--)
    {
        char currentT = t[tIndex];
        int firstSameSIndex = sSize - 1;
        bool isFindSameChar = false;
        for (int sIndex = firstSameSIndex; sIndex >= 0; sIndex--)
        {
            if (sIndex < tIndex)
            {
                break;
            }

            if (s[sIndex] == currentT)
            {
                isFindSameChar = true;

                if ((sIndex < firstSameSIndex) && (firstSameSIndex == sSize - 1))
                {
                    firstSameSIndex = sIndex;
                }

                bool isLastChar = (tIndex == tSize - 1);
                if (isLastChar)
                {
                    dp[tIndex][sIndex] = 1;
                }
                else
                {
                    unsigned int number = 0;
                    int nextTIndex = tIndex + 1;
                    for (int i = sIndex + 1; i < sSize; i++)
                    {
                        number += dp[nextTIndex][i];
                    }
                    dp[tIndex][sIndex] = number;
                }
            }
        }

        if (!isFindSameChar)
        {
            break;
        }
    }

    int result = 0;
    if (tSize > 0)
    {
        for (int i = 0; i < sSize; i++)
        {
            result += dp[0][i];
        }
    }

    for (int i = 0; i < tSize; i++)
    {
        free(dp[i]);
    }
    free(dp);

    return result;
}
