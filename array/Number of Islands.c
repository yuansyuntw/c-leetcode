char** gGrid;
int gGridSize;
int gGridColSize;

int gGroupCount;

bool visit(int r, int c) {
    bool isSuccess = false;
    if ((r>=0) && (r<gGridSize) && (c>=0) && (c<gGridColSize) && gGrid[r][c]=='1') {
        // Changing content for visited cell rather than creating a table for saving memory
        gGrid[r][c] = '0';
        isSuccess = true;
    }
    
    return isSuccess;
}

void connect(int r, int c) {
    if (visit(r, c)) {
        connect(r-1, c);
        connect(r+1, c);
        connect(r, c-1);
        connect(r, c+1);
    }
}


int numIslands(char** grid, int gridSize, int* gridColSize){
    gGrid = grid;
    gGridSize = gridSize;
    gGridColSize = *gridColSize;
    gGroupCount = 0;
    
    for (int r=0;r<gGridSize;r++) {
        for(int c=0;c<gGridColSize;c++) {
            if (grid[r][c] == '1') {
                connect(r, c);
                gGroupCount++;
            }
        }
    }
    
    return gGroupCount;
}