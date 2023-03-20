// 1. create a graph
// 2. BFS the graph
// 3. if reach endWord, we return the step.

int gWordListSize;

struct Item
{
    char *pattern;
    int *adjacencyList;
    int adjacencyListSize;
    UT_hash_handle hh;
};

struct Patterns
{
    char **list;
    int size;
};

struct Patterns *
getPatterns(char *word)
{
    int length = strlen(word);
    struct Patterns *result = (struct Patterns *)calloc(1, sizeof(struct Patterns));
    result->list = (char **)calloc(length, sizeof(char *));
    for (int i = 0; i < length; i++)
    {
        char *copy = strdup(word);
        copy[i] = '*';
        result->list[result->size++] = copy;
    }
    return result;
}

void freePatterns(struct Patterns *patterns)
{
    for (int i = 0; i < patterns->size; i++)
    {
        free(patterns->list[i]);
    }
    free(patterns);
}

void freeDictionary(struct Item **dictionary)
{
    struct Item *currentItem, *tempItem;
    HASH_ITER(hh, *dictionary, currentItem, tempItem)
    {
        HASH_DEL(*dictionary, currentItem);
        free(currentItem->adjacencyList);
        free(currentItem->pattern);
        free(currentItem);
    }
}

void addToDictionary(struct Item **dictionary, char *patternString, int wordIndex)
{
    struct Item *item;
    HASH_FIND_STR(*dictionary, patternString, item);
    if (item == NULL)
    {
        item = (struct Item *)calloc(1, sizeof(struct Item));
        item->pattern = strdup(patternString);
        item->adjacencyList = (int *)calloc(gWordListSize, sizeof(int));
    }
    else
    {
        HASH_DEL(*dictionary, item);
    }
    if (item != NULL)
    {
        item->adjacencyList[item->adjacencyListSize++] = wordIndex;
        HASH_ADD_KEYPTR(hh, *dictionary, item->pattern, strlen(item->pattern), item);
    }
}

struct Item *getItem(struct Item **dictionary, char *pattern)
{
    struct Item *item;
    HASH_FIND_STR(*dictionary, pattern, item);
    return item;
}

bool addAdjacencyIntoQueue(char *word, struct Item **dictionary, int *queue, int *queueCount, int *wasSeen, int endWordIndex)
{
    struct Patterns *patterns = getPatterns(word);
    if (patterns == NULL)
    {
        return false;
    }

    bool isFinded = false;
    for (int i = 0; i < patterns->size; i++)
    {
        char *pattern = patterns->list[i];
        struct Item *item = getItem(dictionary, pattern);
        if (item == NULL)
        {
            continue;
        }
        int *adjacencyList = item->adjacencyList;
        int adjacencySize = item->adjacencyListSize;
        for (int adjacencyIndex = 0; adjacencyIndex < adjacencySize; adjacencyIndex++)
        {
            int wordIndex = adjacencyList[adjacencyIndex];
            if (wordIndex == endWordIndex)
            {
                isFinded = true;
                break;
            }
            if (!wasSeen[wordIndex])
            {
                queue[*queueCount] = wordIndex;
                (*queueCount)++;
                wasSeen[wordIndex] = 1;
            }
        }
        if (isFinded)
        {
            break;
        }
    }
    freePatterns(patterns);
    return isFinded;
}

int ladderLength(char *beginWord, char *endWord, char **wordList, int wordListSize)
{
    int beginWordIndex = -1;
    int endWordIndex = -1;
    bool isExitEndWord = false;
    for (int i = 0; i < wordListSize; i++)
    {
        if (strcmp(wordList[i], beginWord) == 0)
        {
            beginWordIndex = i;
        }
        if (strcmp(wordList[i], endWord) == 0)
        {
            isExitEndWord = true;
            endWordIndex = i;
        }
    }
    if (!isExitEndWord)
    {
        return 0;
    }

    struct Item *dictionary = NULL;
    gWordListSize = wordListSize;

    for (int i = 0; i < wordListSize; i++)
    {
        struct Patterns *patterns = getPatterns(wordList[i]);
        if (patterns == NULL)
        {
            continue;
        }
        for (int patternIndex = 0; patternIndex < patterns->size; patternIndex++)
        {
            char *pattern = patterns->list[patternIndex];
            addToDictionary(&dictionary, pattern, i);
        }
        freePatterns(patterns);
    }

    int step = 1;
    int *wasSeen = (int *)calloc(wordListSize, sizeof(int));
    int *queue = (int *)calloc(wordListSize, sizeof(int));
    int fronOfQueue = 0;
    int queueCount = 0;

    if (beginWordIndex != -1)
    {
        wasSeen[beginWordIndex] = 1;
    }
    bool isStop = addAdjacencyIntoQueue(beginWord, &dictionary, queue, &queueCount, wasSeen, endWordIndex);

    if (!isStop)
    {
        while (fronOfQueue < queueCount)
        {
            step++;
            int start = fronOfQueue;
            int end = queueCount;
            for (int i = start; i < end; i++)
            {
                int wordIndex = queue[i];
                char *word = wordList[wordIndex];
                isStop = addAdjacencyIntoQueue(word, &dictionary, queue, &queueCount, wasSeen, endWordIndex);
                if (isStop)
                {
                    break;
                }
            }
            fronOfQueue = end;
            if (isStop)
            {
                break;
            }
        }
    }

    free(queue);
    free(wasSeen);
    freeDictionary(&dictionary);

    bool isFinded = isStop;
    if (isFinded)
    {
        return step + 1;
    }

    return 0;
}
