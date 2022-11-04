typedef struct
{
    bool isOperator;
    long number;
    char operator;
} Item;

int stackCount;
Item **stack;

Item *getItem(char *input)
{
    Item *item = (Item *)calloc(1, sizeof(Item));
    item->number = strtol(input, NULL, 10);

    if (item->number == 0)
    {
        char operator= input[0];
        item->isOperator = ((operator== '+') ||
                            (operator== '-') ||
                            (operator== '*') ||
                            (operator== '/'));
        if (item->isOperator)
        {
            item->number = INT_MAX;
            item->operator= operator;
        }
    }

    return item;
}

void checkAndComputeStack()
{
    if (stackCount < 3)
    {
        return;
    }

    int operatorItemIndex = stackCount - 1;
    bool shouldCompute = stack[operatorItemIndex]->isOperator;
    if (shouldCompute == false)
    {
        return;
    }

    char operator= stack[operatorItemIndex]->operator;

    int rightItemIndex = stackCount - 2;
    long rightNumber = stack[rightItemIndex]->number;

    int leftItemIndex = stackCount - 3;
    long leftNumber = stack[leftItemIndex]->number;

    long result = 0;
    switch (operator)
    {
    case '+':
        result = leftNumber + rightNumber;
        break;
    case '-':
        result = leftNumber - rightNumber;
        break;
    case '*':
        result = leftNumber * rightNumber;
        break;
    case '/':
        result = leftNumber / rightNumber;
        break;
    default:
        break;
    }

    stackCount -= 2;
    free(stack[operatorItemIndex]);
    free(stack[rightItemIndex]);

    stack[leftItemIndex]->number = result;
}

int evalRPN(char **tokens, int tokensSize)
{
    stackCount = 0;
    stack = (Item **)calloc(tokensSize, sizeof(Item *));
    for (int i = 0; i < tokensSize; i++)
    {
        char *input = tokens[i];
        Item *item = getItem(input);
        stack[stackCount++] = item;
        checkAndComputeStack();
    }

    int result = stack[0]->number;

    for (int i = 0; i < stackCount; i++)
    {
        free(stack[i]);
    }
    free(stack);

    if (stackCount != 1)
    {
        printf("something wrong\n");
        return 0;
    }

    return result;
}
