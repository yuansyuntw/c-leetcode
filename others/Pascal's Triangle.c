/**
 * Return an array of arrays of size *returnSize.
 * The sizes of the arrays are returned as *returnColumnSizes array.
 * Note: Both returned array and *columnSizes array must be malloced, assume caller calls free().
 */
int** generate(int numRows, int* returnSize, int** returnColumnSizes){
    *returnSize = numRows;
    *returnColumnSizes = malloc(sizeof(int) * numRows);
    
    int **pascalTable = malloc(sizeof(int*) * numRows);
    for(int i=0; i<numRows; i++) {
        int numberOfColumn = i+1;
        returnColumnSizes[0][i] = numberOfColumn;
        pascalTable[i] = malloc(sizeof(int) * numberOfColumn);
        
        for(int j=0; j<numberOfColumn; j++) {
            if ((j == 0) || (j == i)) {
                pascalTable[i][j] = 1;
            } else {
                pascalTable[i][j] = pascalTable[i-1][j-1] + pascalTable[i-1][j];
            }
        }
    }
    
    return pascalTable;
}