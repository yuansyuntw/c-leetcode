int** g_returnIntervals;
int* g_returnColumsSizes;
int g_columnSize;
int g_returnSize;

void addInterval(int* intervals) {
    g_returnIntervals[g_returnSize] = malloc(sizeof(int)*g_columnSize);
    if (g_returnIntervals == NULL) {
        return;
    }
    
    g_returnIntervals[g_returnSize][0] = intervals[0];
    g_returnIntervals[g_returnSize][1] = intervals[1];
    g_returnColumsSizes[g_returnSize] = g_columnSize;
    g_returnSize++;
}

/**
 * Return an array of arrays of size *returnSize.
 * The sizes of the arrays are returned as *returnColumnSizes array.
 * Note: Both returned array and *columnSizes array must be malloced, assume caller calls free().
 */
int** insert(int** intervals, int intervalsSize, int* intervalsColSize, int* newInterval, int newIntervalSize, int* returnSize, int** returnColumnSizes) {
    g_returnSize = 0;
    g_columnSize = 2;
    g_returnIntervals = malloc(sizeof(int*) * (intervalsSize+1));
    if (g_returnIntervals == NULL) {
        return intervals;
    }
    
    g_returnColumsSizes = malloc(sizeof(int) * (intervalsSize+1));
    if (g_returnColumsSizes == NULL) {
        return intervals;
    }
    
    if (intervalsSize == 0) {
        addInterval(newInterval);
        *returnSize = g_returnSize;
        *returnColumnSizes = g_returnColumsSizes;
        return g_returnIntervals;
    }
    
    // new interval include all intervals
    if ((newInterval[0] <= intervals[0][0]) && (newInterval[1] >= intervals[intervalsSize-1][1])) {
        addInterval(newInterval);
        *returnSize = g_returnSize;
        *returnColumnSizes = g_returnColumsSizes;
        return g_returnIntervals;
    }

    // find the start insert index
    int startInsertIndex = 0;
    for (int i=0; i<intervalsSize; i++) {
        if(newInterval[0] > intervals[i][0]) {
            addInterval(intervals[i]);
        } else {
            startInsertIndex = i;
            break;
        }
    }

    // insert
    if (g_returnSize > 0) {
        if (g_returnIntervals[g_returnSize-1][1] >= newInterval[0]) {
            if (g_returnIntervals[g_returnSize-1][1] < newInterval[1]) {
                g_returnIntervals[g_returnSize-1][1] = newInterval[1];
            }
        } else {
            addInterval(newInterval);
        }
    } else {
        addInterval(newInterval);
    }
    
    // merge
    for (int i=startInsertIndex; i<intervalsSize; i++) {
        if (g_returnIntervals[g_returnSize-1][1] >= intervals[i][0]) {
            if (g_returnIntervals[g_returnSize-1][1] < intervals[i][1]) {
                g_returnIntervals[g_returnSize-1][1] = intervals[i][1];
            }
        } else {
            addInterval(intervals[i]);
        }
    }
    
    *returnSize = g_returnSize;
    *returnColumnSizes = g_returnColumsSizes;
    return g_returnIntervals;
}