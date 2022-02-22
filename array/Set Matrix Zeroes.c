

void setZeroes(int** matrix, int matrixSize, int* matrixColSize){
    bool isMakeFirstRowToZero = false;
    
    // To speed up the time when accessing the col size
    int colSize = *matrixColSize;

    for (int c=0; c<colSize; c++) {
        if (matrix[0][c] == 0) {
            isMakeFirstRowToZero = true;
            break;
        }
    }
    
    bool isMakeFirstColToZero = false;
    for (int r=0; r<matrixSize; r++) {
        if (matrix[r][0] == 0) {
            isMakeFirstColToZero = true;
            break;
        }
    }
    
    for (int r=1; r<matrixSize; r++) {
        for (int c=1; c<colSize; c++) {
            if (matrix[r][c] == 0) {
                matrix[0][c] = 0;
                matrix[r][0] = 0;
            }
        }
    }
    
    for (int r=1; r<matrixSize; r++) {
        for (int c=1; c<colSize; c++) {
            if ((matrix[r][0] == 0) || (matrix[0][c] == 0)) {
                matrix[r][c] = 0;
            }
        }
    }
    
    if (isMakeFirstColToZero) {
        for (int r=0; r<matrixSize; r++) {
            matrix[r][0] = 0;
        }
    }
    
    if (isMakeFirstRowToZero) {
        for (int c=0; c<colSize; c++) {
            matrix[0][c] = 0;
        }
    }
}