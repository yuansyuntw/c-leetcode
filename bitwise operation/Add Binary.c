int char2Int(char value)
{
    switch (value)
    {
    case '0':
        return 0;
    case '1':
        return 1;
    default:
        return 0; // something wrong.
    }
}

char int2Char(int value)
{
    switch (value)
    {
    case 0:
        return '0';
    case 1:
        return '1';
    default:
        return ' '; // something wrong.
    }
}

void add(int aValue, int bValue, int *sum, int *carry)
{
    int result = aValue + bValue + *carry;
    *sum = result % 2;
    *carry = result / 2;
}

char *addBinary(char *a, char *b)
{
    int aLength = strlen(a); // Does not contain the '/0'.
    int bLength = strlen(b);

    int resultLength = aLength;
    if (bLength > aLength)
    {
        resultLength = bLength;
    }
    char *result = (char *)calloc(resultLength + 1, sizeof(char)); // Add one for '\0'.
    result[resultLength] = '\0';

    int aIndex = aLength - 1;
    int bIndex = bLength - 1;
    int carry = 0;
    int resultIndex = resultLength - 1;
    while ((aIndex >= 0) && (bIndex >= 0))
    {
        int sum = 0;
        int aValue = char2Int(a[aIndex--]);
        int bValue = char2Int(b[bIndex--]);
        add(aValue, bValue, &sum, &carry);
        result[resultIndex--] = int2Char(sum);
    }

    while (aIndex >= 0)
    {
        int sum = 0;
        int aValue = char2Int(a[aIndex--]);
        add(aValue, 0, &sum, &carry);
        result[resultIndex--] = int2Char(sum);
    }

    while (bIndex >= 0)
    {
        int sum = 0;
        int bValue = char2Int(b[bIndex--]);
        add(0, bValue, &sum, &carry);
        result[resultIndex--] = int2Char(sum);
    }

    if (carry != 0)
    {
        int newLength = resultLength + 1;                               // One for the carry.
        char *copyResult = (char *)calloc(newLength + 1, sizeof(char)); // One for `\0`.
        if (copyResult == NULL)
        {
            return NULL;
        }

        sprintf(copyResult, "%c%s", int2Char(carry), result);
        char *tempResult = result;
        result = copyResult;
        free(tempResult);
    }

    return result;
}
