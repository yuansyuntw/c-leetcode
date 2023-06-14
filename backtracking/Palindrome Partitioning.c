struct Item
{
    int startIndex;
    int endIndex;
};

char *gS;
int gSLength;

int resultSize;
char ***result;
int *resultLengths;
int resultCount;

int itemsCount;
struct Item **items;

bool isPalindrome(int startIndex, int endIndex)
{
    bool result = true;
    while (startIndex < endIndex)
    {
        if (gS[startIndex] != gS[endIndex])
        {
            result = false;
            break;
        }
        startIndex++;
        endIndex--;
    }

    return result;
}

void reallocResultIfNeeded()
{
    if (resultCount >= (resultSize - 1))
    {
        resultSize = resultSize * 2;
        result = realloc(result, sizeof(char **) * resultSize);
        resultLengths = realloc(resultLengths, sizeof(int) * resultSize);
    }
}

void addItemsToResult()
{
    if (itemsCount == 0)
    {
        return;
    }
    reallocResultIfNeeded();

    char **copyList = (char **)calloc(itemsCount, sizeof(char *));
    for (int i = 0; i < itemsCount; i++)
    {
        struct Item *item = items[i];
        int length = item->endIndex - item->startIndex + 1;
        char *part = (char *)calloc(length, sizeof(char *));
        int count = 0;
        for (int i = item->startIndex; i <= item->endIndex; i++)
        {
            part[count++] = gS[i];
        }
        part[length] = '\0';
        copyList[i] = part;
    }

    result[resultCount] = copyList;
    resultLengths[resultCount] = itemsCount;
    resultCount++;
}

struct Item *createItem(int startIndex, int endIndex)
{
    struct Item *newItem = (struct Item *)calloc(1, sizeof(struct Item));
    newItem->startIndex = startIndex;
    newItem->endIndex = endIndex;
    return newItem;
}

void backtracking(int index, int max)
{
    if (index > max)
    {
        addItemsToResult();
        return;
    }

    for (int i = index; i < gSLength; i++)
    {
        if (isPalindrome(index, i))
        {
            struct Item *newItem = createItem(index, i);
            items[itemsCount++] = newItem;
            backtracking(i + 1, max);
            free(items[--itemsCount]);
        }
    }
}

/**
 * Return an array of arrays of size *returnSize.
 * The sizes of the arrays are returned as *returnColumnSizes array.
 * Note: Both returned array and *columnSizes array must be malloced, assume caller calls free().
 */

char ***partition(char *s, int *returnSize, int **returnColumnSizes)
{
    gS = s;
    gSLength = strlen(s);

    resultSize = gSLength;
    result = (char ***)calloc(resultSize, sizeof(char **));
    resultLengths = (int *)calloc(resultSize, sizeof(int));
    resultCount = 0;

    if (gSLength > 1)
    {
        itemsCount = 0;
        items = (struct Item **)calloc(gSLength, sizeof(struct Item *));
        backtracking(0, gSLength - 1);
        free(items);
    }
    else
    {
        char **newList = (char **)calloc(1, sizeof(char *));
        newList[0] = s;
        result[resultCount] = newList;
        resultLengths[resultCount] = 1;
        resultCount++;
    }

    *returnSize = resultCount;
    *returnColumnSizes = resultLengths;
    return result;
}
