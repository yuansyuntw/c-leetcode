int min(int value1, int value2) {
    if (value1 < value2) {
        return value1;
    }

    return value2;
}

int getArea(int** areaMap, int rowMax, int colMax, int row, int col, int failValue) {
    if ((row >= 0) && (row < rowMax) &&
        (col >= 0) && (col < colMax)) {
        return areaMap[row][col];
    }

    return failValue;
}

int maximalSquare(char** matrix, int matrixSize, int* matrixColSize) {
    int rowSize = matrixSize;
    int colSize = matrixColSize[0];

    int** dp = (int**)calloc(rowSize, sizeof(int*));

    int maxArea = 0;
    for (int r = rowSize - 1; r >= 0; r--) {
        dp[r] = (int*)calloc(colSize, sizeof(int));
        for (int c = colSize - 1; c >= 0; c--) {
            int area = (matrix[r][c] == '1') ? 1 : 0;
            bool isSkip = (area == 0);
            if (isSkip) {
                dp[r][c] = area;
                continue;
            }

            int outOfRangeArea = 0;
            int smallestArea = getArea(dp, rowSize, colSize, r + 1, c, outOfRangeArea);
            smallestArea = min(smallestArea, getArea(dp, rowSize, colSize, r + 1, c + 1, outOfRangeArea));
            smallestArea = min(smallestArea, getArea(dp, rowSize, colSize, r, c + 1, outOfRangeArea));
            area = smallestArea + 1;

            dp[r][c] = area;

            if (area > maxArea) {
                maxArea = area;
            }
        }
    }

    for (int row = 0; row < rowSize; row++) {
        free(dp[row]);
    }
    free(dp);

    return maxArea * maxArea;
}