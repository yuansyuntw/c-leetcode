const charTableSize = 26;

int char2Int(char c)
{
    int result = c - 'a';
    if ((result >= 0) && (result < charTableSize))
    {
        return result;
    }
    return 0;
}

bool checkInclusion(char *s1, char *s2)
{
    if (strlen(s2) < strlen(s1))
    {
        return false;
    }

    int *s1Table = (int *)calloc(charTableSize, sizeof(int));
    int *s2Table = (int *)calloc(charTableSize, sizeof(int));
    for (int i = 0; i < strlen(s1); i++)
    {
        s1Table[char2Int(s1[i])]++;
        s2Table[char2Int(s2[i])]++;
    }

    int diffCount = 0;
    int *diffTable = (int *)calloc(charTableSize, sizeof(int));
    for (int i = 0; i < charTableSize; i++)
    {
        diffTable[i] = s1Table[i] - s2Table[i];
        if (diffTable[i] != 0)
        {
            diffCount++;
        }
    }

    bool result = false;
    if (diffCount == 0)
    {
        result = true;
    }

    for (int i = 1; i <= (strlen(s2) - strlen(s1)) && !result; i++)
    {
        int removedChar = char2Int(s2[i - 1]);
        int addedChar = char2Int(s2[i + strlen(s1) - 1]);

        diffTable[removedChar]++;
        if (diffTable[removedChar] == 0)
        {
            diffCount--;
        }
        else if (diffTable[removedChar] == 1)
        {
            diffCount++;
        }

        diffTable[addedChar]--;
        if (diffTable[addedChar] == 0)
        {
            diffCount--;
        }
        else if (diffTable[addedChar] == -1)
        {
            diffCount++;
        }

        if (diffCount == 0)
        {
            result = true;
            break;
        }
    }

    free(s1Table);
    free(s2Table);
    free(diffTable);

    return result;
}
