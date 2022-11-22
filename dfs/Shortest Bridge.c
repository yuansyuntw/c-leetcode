typedef struct
{
    int r;
    int c;
    int step;
} Item;

int **gGrid;
int ROW_SIZE;
int COL_SIZE;

int SEA = 0;
int ISLAND = 1;

int stackSize;
int stackTop;
int stackBottom;
Item **stack;

bool **isSeenTable;

void stackPush(int row, int col, int step)
{
    if ((row < 0) || (row >= ROW_SIZE) ||
        (col < 0) || (col >= COL_SIZE))
    {
        return;
    }

    if (isSeenTable[row][col])
    {
        return;
    }

    isSeenTable[row][col] = true;

    Item *newItem = (Item *)calloc(1, sizeof(Item));
    newItem->r = row;
    newItem->c = col;
    newItem->step = step;
    stack[stackTop] = newItem;

    stackTop = ((stackTop + 1) % stackSize);
}

Item *stackPop()
{
    if (stackBottom == stackTop)
    {
        return NULL;
    }

    Item *bottom = stack[stackBottom];
    stack[stackBottom] = NULL;

    stackBottom = ((stackBottom + 1) % stackSize);

    return bottom;
}

bool stackIsEmpty()
{
    return (stackBottom == stackTop);
}

void serachSameIsland(int row, int col)
{
    if ((row < 0) || (row >= ROW_SIZE) ||
        (col < 0) || (col >= COL_SIZE))
    {
        return;
    }

    if (gGrid[row][col] == ISLAND)
    {
        gGrid[row][col] = -1;
        serachSameIsland(row + 1, col);
        serachSameIsland(row - 1, col);
        serachSameIsland(row, col + 1);
        serachSameIsland(row, col - 1);
    }
    else
    {
        // First step
        stackPush(row, col, 1);
    }
}

bool checkAnotherIslandAndPushStack(int row, int col, int step)
{
    if ((row < 0) || (row >= ROW_SIZE) ||
        (col < 0) || (col >= COL_SIZE))
    {
        return false;
    }

    if (gGrid[row][col] == ISLAND)
    {
        return true;
    }

    if (gGrid[row][col] == SEA)
    {
        stackPush(row, col, step);
    }

    return false;
}

int shortestBridge(int **grid, int gridSize, int *gridColSize)
{
    gGrid = grid;
    ROW_SIZE = gridSize;
    COL_SIZE = gridColSize[0];

    stackSize = ROW_SIZE * COL_SIZE;
    stackTop = 0;
    stackBottom = 0;
    stack = (Item **)calloc(ROW_SIZE * COL_SIZE, sizeof(Item *));

    isSeenTable = (bool **)calloc(ROW_SIZE, sizeof(bool *));
    for (int r = 0; r < ROW_SIZE; r++)
    {
        isSeenTable[r] = (bool *)calloc(COL_SIZE, sizeof(bool));
    }

    bool isStop = false;
    for (int r = 0; r < ROW_SIZE; r++)
    {
        for (int c = 0; c < COL_SIZE; c++)
        {
            if (grid[r][c] == ISLAND)
            {
                // First step
                stackPush(r, c, 1);
                isStop = true;
                break;
            }
        }

        if (isStop)
        {
            break;
        }
    }

    if (stackIsEmpty())
    {
        printf("Something wrong\n");
        return 0;
    }

    // DFS
    Item *firstItem = stackPop();
    serachSameIsland(firstItem->r, firstItem->c);
    free(firstItem);

    int result = 0;
    while (!stackIsEmpty())
    {
        Item *item = stackPop();
        if (item == NULL)
        {
            break;
        }

        bool isAnotherIsland = false;
        isAnotherIsland = checkAnotherIslandAndPushStack(item->r + 1, item->c, item->step + 1);
        if (isAnotherIsland)
        {
            result = item->step;
            break;
        }

        isAnotherIsland = checkAnotherIslandAndPushStack(item->r - 1, item->c, item->step + 1);
        if (isAnotherIsland)
        {
            result = item->step;
            break;
        }
        isAnotherIsland = checkAnotherIslandAndPushStack(item->r, item->c + 1, item->step + 1);
        if (isAnotherIsland)
        {
            result = item->step;
            break;
        }
        isAnotherIsland = checkAnotherIslandAndPushStack(item->r, item->c - 1, item->step + 1);
        if (isAnotherIsland)
        {
            result = item->step;
            break;
        }

        free(item);
    }

    for (int i = 0; i < stackSize; i++)
    {
        if (stack[i] != NULL)
        {
            free(stack[i]);
        }
    }
    free(stack);

    for (int r = 0; r < ROW_SIZE; r++)
    {
        free(isSeenTable[r]);
    }
    free(isSeenTable);

    return result;
}
