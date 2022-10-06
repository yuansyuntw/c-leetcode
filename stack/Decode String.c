struct Item
{
    int repeatedTime;
    char *tempString;
};

struct Item **stack;
int stackSize;
int stackCount;

char *emptyString(int length)
{
    return (char *)calloc(length, sizeof(char));
}

void push(char *tempString, int repeatedTime)
{
    struct Item *newItem = (struct Item *)calloc(1, sizeof(struct Item));
    newItem->tempString = tempString;
    newItem->repeatedTime = repeatedTime;
    stack[stackCount++] = newItem;
}

struct Item *pop()
{
    if (stackCount <= 0)
    {
        return NULL;
    }

    struct Item *top = stack[stackCount - 1];
    stackCount--;
    
    return top;
}

char *decodeString(char *s)
{
    stackSize = 30;
    stack = (struct Item **)calloc(stackSize, sizeof(struct Item *));
    stackCount = 0;

    int sLength = strlen(s);
    char *currentString = emptyString(100001);
    char *repeatedNumberString = calloc(4, sizeof(char));
    for (int i = 0; i < sLength; i++)
    {
        char currentChar = s[i];

        bool isNumber = ((currentChar >= '0') && (currentChar <= '9'));
        if (isNumber)
        {
            sprintf(repeatedNumberString, "%s%c", repeatedNumberString, currentChar);
            continue;
        }

        bool isStart = (currentChar == '[');
        if (isStart)
        {
            int repeatedNumber = atoi(repeatedNumberString);
            push(currentString, repeatedNumber);

            currentString = emptyString(100000);
            sprintf(repeatedNumberString, "");

            continue;
        }

        bool isEnd = (currentChar == ']');
        if (isEnd)
        {
            struct Item *item = pop();
            if (item != NULL)
            {
                char *copyString = strdup(currentString);
                for (int i = 0; i < item->repeatedTime - 1; i++)
                {
                    strcat(currentString, copyString);
                }
                free(copyString);

                // tempString + currentString
                strcat(item->tempString, currentString);
                free(currentString);

                currentString = item->tempString;
                item->tempString = NULL;
                free(item);
            }

            continue;
        }

        // currentString + currentChar;
        sprintf(currentString, "%s%c", currentString, currentChar);
    }

    for (int i = 0; i < stackCount; i++)
    {
        if (stack[i] != NULL)
        {
            if (stack[i]->tempString != NULL)
            {
                free(stack[i]->tempString);
            }
            free(stack[i]);
        }
    }
    free(stack);

    return currentString;
}