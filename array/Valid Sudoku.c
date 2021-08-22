int* get_dict(int board_length) {
    int* dict = (int*)malloc(board_length * sizeof(int));
    for(int i=0;i<board_length;i++){
        // should be initialized
        dict[i] = 0;
    }
    
    return dict;
}

int get_index(char c) {
    if (c == '.') {
        return 0;
    }
    
    return ((int)c - (int)'0');
}

bool isValidSudoku(char** board, int boardSize, int* boardColSize){    
    for (int i=0; i<*boardColSize; i++) {
        int* row_dict = get_dict(*boardColSize + 1);
        for (int j=0; j<*boardColSize; j++) {
            int index = get_index(board[i][j]);
            if (index != 0) {
                if (row_dict[index] == 0) {
                    row_dict[index]++;
                } else {
                    free(row_dict);
                    return false;
                }
            }
        }
        
        free(row_dict);
    }
    
    for (int i=0; i<*boardColSize; i++) {
        int* col_dict = get_dict(*boardColSize + 1);
        for (int j=0; j<*boardColSize; j++) {
            int index = get_index(board[j][i]);
            if (index != 0) {
                if (col_dict[index] == 0) {
                    col_dict[index]++;
                } else {
                    free(col_dict);
                    return false;
                }
            }

        }
        
        free(col_dict);
    }
    
    for (int center_col = 1; center_col < 9; center_col += 3) {
        for (int center_row = 1; center_row < 9; center_row += 3) {
            int* dict = get_dict(10);
            for (int i=center_col-1; i<=center_col+1; i++) {
                for (int j=center_row-1; j<=center_row+1; j++) {     
                    int index = get_index(board[i][j]);
                    if (index != 0) {
                        if (dict[index] == 0) {
                            dict[index]++;
                        } else {
                            return false;
                        }                        
                    }        
                }
            }
        }
    }
    
    return true;
}