struct Cell
{
    int row;
    int col;
};

int seenCount;
int **isSeenTable;
char **gboard;
int rowSize;
int colSize;

int currentStackSize;
struct Cell **currentStack;

void updateOToXInStack()
{
    for (int i = 0; i < currentStackSize; i++)
    {
        struct Cell *cell = currentStack[i];
        gboard[cell->row][cell->col] = 'X';
        free(cell);
    }
    currentStackSize = 0;
}

void clearStack()
{
    for (int i = 0; i < currentStackSize; i++)
    {
        free(currentStack[i]);
    }
    currentStackSize = 0;
}

bool isSurrounded(int row, int col)
{
    if ((row < 0) || (row >= rowSize) || (col < 0) || (col >= colSize))
    {
        return false;
    }

    bool isSeen = isSeenTable[row][col];
    if (isSeen)
    {
        return true;
    }
    isSeenTable[row][col] = 1;
    seenCount++;

    bool isO = (gboard[row][col] == 'O');
    if (!isO)
    {
        return true;
    }

    struct Cell *cell = (struct Cell *)calloc(1, sizeof(struct Cell));
    cell->row = row;
    cell->col = col;
    currentStack[currentStackSize++] = cell;

    bool isSurroundedByX = true;
    isSurroundedByX = isSurroundedByX & isSurrounded(row + 1, col);
    isSurroundedByX = isSurroundedByX & isSurrounded(row - 1, col);
    isSurroundedByX = isSurroundedByX & isSurrounded(row, col + 1);
    isSurroundedByX = isSurroundedByX & isSurrounded(row, col - 1);

    return isSurroundedByX;
}

void solve(char **board, int boardSize, int *boardColSize)
{
    gboard = board;
    rowSize = boardSize;
    colSize = boardColSize[0];

    currentStackSize = 0;
    currentStack = (struct Cell **)calloc(rowSize * colSize, sizeof(struct Cell *));

    seenCount = 0;
    isSeenTable = (int **)calloc(boardSize, sizeof(int *));
    for (int i = 0; i < boardSize; i++)
    {
        isSeenTable[i] = (int *)calloc(boardColSize[i], sizeof(int));
    }

    bool isStop = false;
    for (int row = 0; row < boardSize; row++)
    {
        for (int col = 0; col < boardColSize[row]; col++)
        {
            bool isSurround = isSurrounded(row, col);
            if (isSurround)
            {
                updateOToXInStack();
            }
            else
            {
                clearStack();
            }

            isStop = (seenCount == rowSize * colSize);
            if (isStop)
            {
                break;
            }
        }

        if (isStop)
        {
            break;
        }
    }

    for (int i = 0; i < boardSize; i++)
    {
        free(isSeenTable[i]);
    }
    free(isSeenTable);

    clearStack();
    free(currentStack);
}