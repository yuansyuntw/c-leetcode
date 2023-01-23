#define maxLetterSize 4
char **digitToLetters[10][maxLetterSize] = {
    {' ', ' ', ' ', ' '}, // 0
    {' ', ' ', ' ', ' '}, // 1
    {'a', 'b', 'c', ' '}, // 2
    {'d', 'e', 'f', ' '}, // 3
    {'g', 'h', 'i', ' '}, // 4
    {'j', 'k', 'l', ' '}, // 5
    {'m', 'n', 'o', ' '}, // 6
    {'p', 'q', 'r', 's'}, // 7
    {'t', 'u', 'v', ' '}, // 8
    {'w', 'x', 'y', 'z'}, // 9
};
int digitsLegth;
char *gDigits;
int resultCount;
char **result;

char *copyCombination(char *combination)
{
    int size = strlen(combination);
    char *newCombination = (char *)calloc(size + 1, sizeof(char));
    for (int i = 0; i < size; i++)
    {
        newCombination[i] = combination[i];
    }
    newCombination[size] = '\0';

    return newCombination;
}

void dfs(int currentDigitIndex, char *currentCombination)
{
    int digit = gDigits[currentDigitIndex] - '0';

    int letterIndex = 0;
    while (letterIndex < maxLetterSize)
    {
        char letter = digitToLetters[digit][letterIndex];
        if (letter == ' ')
        {
            break;
        }

        currentCombination[currentDigitIndex] = letter;
        currentCombination[currentDigitIndex + 1] = '\0';

        int currentLegth = currentDigitIndex + 1;
        if (currentLegth == digitsLegth)
        {
            char *savedCombination = copyCombination(currentCombination);
            int size = strlen(savedCombination);
            result[resultCount] = (char *)calloc(size, sizeof(char));
            result[resultCount] = savedCombination;
            resultCount++;
        }
        else
        {
            dfs(currentDigitIndex + 1, currentCombination);
        }

        letterIndex++;
    }
}

/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
char **letterCombinations(char *digits, int *returnSize)
{
    gDigits = digits;
    digitsLegth = strlen(digits);

    int resultSize = pow(maxLetterSize, digitsLegth);
    resultCount = 0;
    result = (char **)calloc(resultSize, sizeof(char *));

    char *currentCombination = (char *)calloc(maxLetterSize + 1, sizeof(char));
    if (digitsLegth > 0)
    {
        dfs(0, currentCombination);
    }

    free(currentCombination);

    *returnSize = resultCount;
    return result;
}