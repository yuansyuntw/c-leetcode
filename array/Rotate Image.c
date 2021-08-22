void rotate(int** matrix, int matrixSize, int* matrixColSize){
    int cycle_width = matrixSize;
    int cycle_index = 0;
    while (cycle_width > 1) {
        int *temp_top = (int*)malloc(cycle_width * sizeof(int));
        
        for (int i=cycle_index, temp_index=0; i<(cycle_index + cycle_width); i++) {
            temp_top[temp_index] = matrix[cycle_index][i];
            temp_index++;
        }
        
        // rotate left-side
        for (int r=cycle_index; r<(cycle_index + cycle_width); r++) {
            matrix[cycle_index][matrixSize - r - 1] = matrix[r][cycle_index];
        }
        
        // rotate bottom-side
        for (int c=cycle_index; c<(cycle_index + cycle_width); c++) {
            matrix[c][cycle_index] = matrix[matrixSize - cycle_index - 1][c];
        }
        
        // rotate right-side
        for (int r=cycle_index; r<(cycle_index + cycle_width); r++) {
            matrix[matrixSize - cycle_index - 1][r] = matrix[matrixSize - r -1][matrixSize - cycle_index - 1];
        }
        
        // rotate top-size
        for (int c=cycle_index, temp_index=0; c<(cycle_index + cycle_width); c++) {
            matrix[matrixSize - c - 1][matrixSize - cycle_index - 1] = temp_top[cycle_width - temp_index - 1];
            temp_index++;
        }
        
        free(temp_top);
        
        cycle_width = cycle_width - 2;
        cycle_index++;
    }
}