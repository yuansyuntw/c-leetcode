int** gHeights;
int gHeightsRowSize;
int gHeightsColSize;

enum Cell {
    Unviewed,
    ViewedAndFlowed
};

int getHeight(int row, int col) {
    if ((row < 0) || (row >= gHeightsRowSize) || (col < 0) || (col >= gHeightsColSize)) {
        return INT_MIN;
    }

    return gHeights[row][col];
}

void dfsMarkFlowed(int** map, int mapRowSize, int mapColSize, int row, int col) {
    if ((row < 0) || (row >= mapRowSize) || (col < 0) || (col >= mapColSize)) return;
    if (map[row][col] != Unviewed) return;
    
    map[row][col] = ViewedAndFlowed;

    int currentHeight = getHeight(row, col);

    int northCol = col - 1;
    int northHeight = getHeight(row, northCol);
    if (northHeight >= currentHeight) {
        dfsMarkFlowed(map, mapRowSize, mapColSize, row, northCol);
    }
    
    int southCol = col + 1;
    int southHeight = getHeight(row, southCol);
    if (southHeight >= currentHeight) {
        dfsMarkFlowed(map, mapRowSize, mapColSize, row, southCol);
    }

    int eastRow = row - 1;
    int eastHeight = getHeight(eastRow, col);
    if (eastHeight >= currentHeight) {
        dfsMarkFlowed(map, mapRowSize, mapColSize, eastRow, col);
    }

    int westRow = row + 1;
    int westHeight = getHeight(westRow, col);
    if (westHeight >= currentHeight) {
        dfsMarkFlowed(map, mapRowSize, mapColSize, westRow, col);
    }
}

/**
 * Return an array of arrays of size *returnSize.
 * The sizes of the arrays are returned as *returnColumnSizes array.
 * Note: Both returned array and *columnSizes array must be malloced, assume caller calls free().
 */
int** pacificAtlantic(int** heights, int heightsSize, int* heightsColSize, int* returnSize, int** returnColumnSizes) {
    gHeights = heights;
    gHeightsRowSize = heightsSize;
    gHeightsColSize = heightsColSize[0];

    int** isFlowPacific = (int**)calloc(sizeof(int*), gHeightsRowSize);
    int** isFlowAtlantic = (int**)calloc(sizeof(int*), gHeightsRowSize);
    for (int h = 0; h < gHeightsRowSize; h++) {
        isFlowPacific[h] = (int*)calloc(sizeof(int), gHeightsColSize);
        isFlowAtlantic[h] = (int*)calloc(sizeof(int), gHeightsColSize);
    }

    int minCol = 0;
    int maxCol = gHeightsColSize - 1;
    for (int r = 0; r < gHeightsRowSize; r++) {
        dfsMarkFlowed(isFlowPacific, gHeightsRowSize, gHeightsColSize, r, minCol);
        dfsMarkFlowed(isFlowAtlantic, gHeightsRowSize, gHeightsColSize, r, maxCol);
    }

    int minRow = 0;
    int maxRow = gHeightsRowSize - 1;
    for (int c = 0; c < gHeightsColSize; c++) {
        dfsMarkFlowed(isFlowPacific, gHeightsRowSize, gHeightsColSize, minRow, c);
        dfsMarkFlowed(isFlowAtlantic, gHeightsRowSize, gHeightsColSize, maxRow, c);
    }

    int count = 0;
    int maxCount = gHeightsRowSize * gHeightsColSize;
    int** results = (int**)calloc(sizeof(int*), maxCount);

    int colSize = 2;
    int rowIndex = 0;
    int colIndex = 1;
    int* colsSize = (int*)calloc(sizeof(int), maxCount);
    for (int i = 0; i < maxCount; i++){
        colsSize[i] = colSize;
        results[i] = (int*)calloc(sizeof(int), colSize);
    }

    for (int r = 0; r < gHeightsRowSize; r++) {
        for (int c = 0; c < gHeightsColSize; c++) {
            if (isFlowPacific[r][c] & isFlowAtlantic[r][c]) {
                int index = count++;
                results[index][rowIndex] = r;
                results[index][colIndex] = c;
            }
        }
    }

    *returnSize = count;
    *returnColumnSizes = colsSize;

    for (int h = 0; h < gHeightsRowSize; h++) {
        free(isFlowPacific[h]);
        free(isFlowAtlantic[h]);
    }
    free(isFlowPacific);
    free(isFlowAtlantic);

    return results;
}