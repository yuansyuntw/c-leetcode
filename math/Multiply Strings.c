bool isZero(char *num)
{
    if ((strlen(num) == 1) && (num[0] == '0'))
    {
        return true;
    }

    return false;
}

int char2Int(char c)
{
    return c - '0';
}

int max(int lhs, int rhs)
{
    if (lhs > rhs)
    {
        return lhs;
    }

    return rhs;
}

typedef struct
{
    int *num;
    int size;
} NumData;

NumData *add(NumData *data1, NumData *data2)
{
    int maxLength = max(data1->size, data2->size);
    int resultIndex = 0;
    int *result = (int *)calloc(maxLength + 1, sizeof(int));

    int carry = 0;
    int num1Index = 0;
    int num2Index = 0;
    while ((num1Index < data1->size) || (num2Index < data2->size) || (carry != 0))
    {
        int value1 = 0;
        if (num1Index < data1->size)
        {
            value1 = data1->num[num1Index++];
        }

        int value2 = 0;
        if (num2Index < data2->size)
        {
            value2 = data2->num[num2Index++];
        }

        int sum = value1 + value2 + carry;
        result[resultIndex++] = sum % 10;
        carry = sum / 10;
    }

    NumData *resultData = (NumData *)calloc(1, sizeof(NumData));
    resultData->num = result;
    resultData->size = resultIndex;

    return resultData;
}

char *multiply(char *num1, char *num2)
{
    if ((isZero(num1)) || (isZero(num2)))
    {
        char *result = (char *)calloc(2, sizeof(char));
        sprintf(result, "0");
        return result;
    }

    int resultSize = 1;
    int *result = (int *)calloc(resultSize, sizeof(int));
    for (int num1Index = strlen(num1) - 1; num1Index >= 0; num1Index--)
    {
        int i1 = char2Int(num1[num1Index]);
        if (i1 == 0)
        {
            continue;
        }

        int carry = 0;
        int lastIndex1 = strlen(num1) - 1;
        int currentIndex = lastIndex1 - num1Index;
        int currentLength = currentIndex + 1;
        int size = (currentLength - 1) + strlen(num2) + 1;

        // low-to-hight weight
        int tempResultIndex = currentIndex;
        int *tmpResult = (int *)calloc(size, sizeof(int));

        int num2Index = strlen(num2) - 1;
        while ((num2Index >= 0) || (carry != 0))
        {
            int i2 = 0;
            if (num2Index >= 0)
            {
                i2 = char2Int(num2[num2Index--]);
            }

            int mulitple = ((i1 * i2) + carry) % 10;
            int newCarry = ((i1 * i2) + carry) / 10;
            tmpResult[tempResultIndex++] = mulitple;
            carry = newCarry;
        }

        NumData *data1 = (NumData *)calloc(1, sizeof(NumData));
        data1->num = result;
        data1->size = resultSize;

        NumData *data2 = (NumData *)calloc(1, sizeof(NumData));
        data2->num = tmpResult;
        data2->size = tempResultIndex;

        NumData *newResultData = add(data1, data2);

        int *oldResult = result;
        result = newResultData->num;
        resultSize = newResultData->size;

        free(oldResult);
        free(tmpResult);
        free(data1);
        free(data2);
        free(newResultData);
    }

    // Translate int* to char*
    char *charResult = (char *)calloc(resultSize + 1, sizeof(char));
    for (int i = 0; i < resultSize; i++)
    {
        int charResultLastIndex = resultSize - 1;
        int charResultIndex = charResultLastIndex - i;
        charResult[charResultIndex] = result[i] + '0';
    }
    charResult[resultSize] = '\0';

    free(result);

    return charResult;
}
