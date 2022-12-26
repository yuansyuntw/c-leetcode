int patternNumber;
int patternSize;
char **patterns;

void parsing(char *p)
{
    int pLength = strlen(p);
    patternSize = pLength;
    patternNumber = 0;
    patterns = (char **)calloc(patternSize, sizeof(char *));
    for (int i = 0; i < pLength; i++)
    {
        char c = p[i];
        bool canCheckNextChar = ((i + 1) < pLength);
        if (canCheckNextChar)
        {
            char nextC = p[i + 1];
            bool isNewPattern = (nextC == '*');
            if (isNewPattern)
            {
                char *pattern = (char *)calloc(3, sizeof(char));
                sprintf(pattern, "%c%c", c, nextC);
                patterns[patternNumber++] = pattern;

                i = i + 1;
                continue;
            }
        }

        char *pattern = (char *)calloc(2, sizeof(char));
        sprintf(pattern, "%c", c);
        patterns[patternNumber++] = pattern;
    }
}

int **dp;

void fillDP(char *s)
{
    int sLength = strlen(s);

    dp = (int **)calloc(sLength, sizeof(int *));
    for (int i = 0; i < sLength; i++)
    {
        dp[i] = (int *)calloc(patternNumber, sizeof(int));
    }

    int pIndex = patternNumber - 1;
    int sIndex = sLength - 1;
    while ((pIndex >= 0) && (sIndex >= 0))
    {
        char *currentPattern = patterns[pIndex];

        // We should check each possibility.
        int subSIndex = sIndex;
        bool isExistMatch = false;
        bool isSetFirstMatchSIndex = false;
        int firstMatchSIndex = subSIndex;
        while (subSIndex >= 0)
        {
            char currentS = s[subSIndex];

            bool isValid = true;
            bool shouldCheckContinue = ((subSIndex < sLength - 1) && (pIndex < patternNumber - 1));
            if (shouldCheckContinue)
            {
                isValid = false;
                int checkSIndex = subSIndex + 1;
                for (int checkPIndex = pIndex + 1; checkPIndex < patternNumber; checkPIndex++)
                {
                    isValid = (dp[checkSIndex][checkPIndex] == 1);
                    if (isValid)
                    {
                        break;
                    }

                    char *checkedPatter = patterns[checkPIndex];
                    if (strlen(checkedPatter) == 1)
                    {
                        break;
                    }
                    else
                    {
                        // Continue to check.
                    }
                }
            }

            if (isValid)
            {
                if (strlen(currentPattern) == 1)
                {
                    bool isMatch = ((currentS == currentPattern[0]) || (currentPattern[0] == '.'));
                    if (isMatch)
                    {
                        dp[subSIndex][pIndex] = 1;
                        isExistMatch = true;
                        if (!isSetFirstMatchSIndex)
                        {
                            isSetFirstMatchSIndex = true;
                            firstMatchSIndex = subSIndex;
                        }
                    }
                    else
                    {
                        // Check the next char.
                    }
                }
                else
                {
                    if (currentPattern[1] == '*')
                    {
                        for (subSIndex; subSIndex >= 0; subSIndex--)
                        {
                            currentS = s[subSIndex];
                            bool isMatch = ((currentS == currentPattern[0]) || (currentPattern[0] == '.'));
                            if (isMatch)
                            {
                                dp[subSIndex][pIndex] = 1;
                                isExistMatch = true;

                                if (!isSetFirstMatchSIndex)
                                {
                                    firstMatchSIndex = subSIndex;
                                    isSetFirstMatchSIndex = true;
                                }
                            }
                            else
                            {
                                // Stop to find the continue char.
                                break;
                            }
                        }
                    }
                }
            }

            subSIndex--;

            bool isLastPattern = (pIndex == patternNumber - 1);
            if (isLastPattern)
            {
                // We stop to check each posiable on the last pattern.
                break;
            }
        }

        if (strlen(currentPattern) == 1)
        {
            if (isExistMatch)
            {
                // Next pattern start from the first match index.
                sIndex = firstMatchSIndex - 1;
                pIndex--;
            }
            else
            {
                // Stop filling the DP
                break;
            }
        }
        else
        {
            if (isExistMatch)
            {
                pIndex--;
            }
            else
            {
                // This pattern can zero match.
                // We jump next pattern.
                pIndex--;
            }
        }
    }
}

bool isMatch(char *s, char *p)
{
    parsing(p);
    fillDP(s);

    bool result = false;
    for (int i = 0; i < patternNumber; i++)
    {
        char *currentPattern = patterns[i];
        if ((strlen(currentPattern) == 1) && (dp[0][i] == 0))
        {
            result = false;
            break;
        }

        if (dp[0][i] == 1)
        {
            result = true;
            break;
        }
    }

    int sLength = strlen(s);
    for (int i = 0; i < sLength; i++)
    {
        free(dp[i]);
    }
    free(dp);

    for (int i = 0; i < patternSize; i++)
    {
        if (patterns[i] != NULL)
        {
            free(patterns[i]);
        }
    }
    free(patterns);

    return result;
}
