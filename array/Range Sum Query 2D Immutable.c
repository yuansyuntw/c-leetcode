typedef struct
{
    int rolSize;
    int colSize;
    int **presumMatrix;
} NumMatrix;

int getPresum(NumMatrix *numMatrix, int row, int col)
{
    if ((row < 0) ||
        (row >= numMatrix->rolSize) ||
        (col < 0) ||
        (col >= numMatrix->colSize))
    {
        return 0;
    }

    return numMatrix->presumMatrix[row][col];
}

NumMatrix *numMatrixCreate(int **matrix, int matrixSize, int *matrixColSize)
{
    NumMatrix *numMatrix = (NumMatrix *)calloc(1, sizeof(NumMatrix));
    numMatrix->rolSize = matrixSize;
    numMatrix->colSize = matrixColSize[0];
    numMatrix->presumMatrix = (int **)calloc(matrixSize, sizeof(int *));
    for (int i = 0; i < matrixSize; i++)
    {
        numMatrix->presumMatrix[i] = (int *)calloc(matrixColSize[0], sizeof(int));
    }

    for (int row = 0; row < matrixSize; row++)
    {
        for (int col = 0; col < matrixColSize[0]; col++)
        {
            int topArea = getPresum(numMatrix, row - 1, col);
            int leftArea = getPresum(numMatrix, row, col - 1);
            int topLeftArea = getPresum(numMatrix, row - 1, col - 1);

            numMatrix->presumMatrix[row][col] =
                matrix[row][col] +
                topArea +
                leftArea +
                -topLeftArea;
        }
    }

    return numMatrix;
}

int numMatrixSumRegion(NumMatrix *obj, int row1, int col1, int row2, int col2)
{
    int rightBottomArea = getPresum(obj, row2, col2);
    int topArea = getPresum(obj, row1 - 1, col2);
    int leftArea = getPresum(obj, row2, col1 - 1);
    int leftTopArea = getPresum(obj, row1 - 1, col1 - 1);
    return rightBottomArea - topArea - leftArea + leftTopArea;
}

void numMatrixFree(NumMatrix *obj)
{
    for (int i = 0; i < obj->rolSize; i++)
    {
        free(obj->presumMatrix[i]);
    }
    free(obj->presumMatrix);
    free(obj);
}
