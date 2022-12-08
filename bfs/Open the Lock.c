const int KEY_SIZE = 4;

typedef struct
{
    char *key;
    int step;
} Item;

int stackStart;
int stackEnd;
int stackSize;
Item **stack;

int *SEEN;

bool isCanAddToStack(char *key)
{
    long index = strtol(key, NULL, 10);
    bool isSeen = SEEN[index];
    return !isSeen;
}

void makeSeen(char *key)
{
    long index = strtol(key, NULL, 10);
    SEEN[index] = 1;
}

bool isEmptyStack()
{
    int newStackStart = (stackStart + 1) % stackSize;
    bool isEmpty = (newStackStart == stackEnd);
    return isEmpty;
}

Item *popStack()
{
    if (isEmptyStack())
    {
        return NULL;
    }

    int newStackStart = (stackStart + 1) % stackSize;
    stackStart = newStackStart;
    Item *result = stack[stackStart];
    stack[stackStart] = NULL;

    return result;
}

void addStack(char *key, int step)
{
    int newStackEnd = (stackEnd + 1) % stackSize;
    bool isFull = (newStackEnd == stackStart);
    if (isFull)
    {
        return;
    }

    Item *newItem = (Item *)calloc(1, sizeof(Item));
    newItem->key = key;
    newItem->step = step;
    stack[stackEnd] = newItem;
    stackEnd = newStackEnd;
}

char *plus(char *key, int index)
{
    char value = key[index];
    value += 1;

    if (value == ('9' + 1))
    {
        value = '0';
    }

    key[index] = value;
    return key;
}

char *minus(char *key, int index)
{
    char value = key[index];
    value -= 1;

    if (value == ('0' - 1))
    {
        value = '9';
    }

    key[index] = value;
    return key;
}

void expore(Item *item)
{
    char *key = item->key;
    int step = item->step;
    for (int i = 0; i < KEY_SIZE; i++)
    {
        char *newPlusKey = plus(strdup(key), i);
        if (isCanAddToStack(newPlusKey))
        {
            addStack(newPlusKey, step + 1);
            makeSeen(newPlusKey);
        }
        else
        {
            free(newPlusKey);
        }

        char *newMiunsKey = minus(strdup(key), i);
        if (isCanAddToStack(newMiunsKey))
        {
            addStack(newMiunsKey, step + 1);
            makeSeen(newMiunsKey);
        }
        else
        {
            free(newMiunsKey);
        }
    }
}

int openLock(char **deadends, int deadendsSize, char *target)
{
    stackStart = -1;
    stackEnd = 0;
    stackSize = ((int)pow(10, KEY_SIZE)) - 1;
    stack = (Item **)calloc(stackSize, sizeof(Item *));

    int seenTableSize = pow(10, KEY_SIZE);
    SEEN = (int *)calloc(seenTableSize, sizeof(int));
    for (int i = 0; i < deadendsSize; i++)
    {
        makeSeen(deadends[i]);
    }

    char *start = (char *)calloc(5, sizeof(char));
    sprintf(start, "0000");
    if (isCanAddToStack(start))
    {
        addStack(start, 0);
        makeSeen(start);
    }
    else
    {
        free(start);
    }

    int result = -1;
    while (true)
    {
        Item *top = popStack();
        if (top == NULL)
        {
            break;
        }

        bool isEqual = (strcmp(top->key, target) == 0);
        if (isEqual)
        {
            result = top->step;
            free(top);
            break;
        }

        expore(top);
        free(top);
    }

    while (!isEmptyStack())
    {
        free(popStack());
    }
    free(stack);
    free(SEEN);

    return result;
}
