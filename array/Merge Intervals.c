int** g_intervals;
int g_intervalsSize;

int g_returnSize;
int* g_returnColumnSizes;
int** g_returnIntervals;

int qSortCompare(void* a, void* b) {
    return ((*(int** )a)[0] - (*(int** )b)[0]);
}

void addInterval(int index) {
    int columnSize = 2;
    g_returnIntervals[g_returnSize] = malloc(sizeof(int) * columnSize);
    if (g_returnIntervals == NULL) {
        return;
    }

    g_returnIntervals[g_returnSize][0] = g_intervals[index][0];
    g_returnIntervals[g_returnSize][1] = g_intervals[index][1];
    g_returnColumnSizes[g_returnSize] = columnSize;
    g_returnSize++;
}

/**
 * Return an array of arrays of size *returnSize.
 * The sizes of the arrays are returned as *returnColumnSizes array.
 * Note: Both returned array and *columnSizes array must be malloced, assume caller calls free().
 */
int** merge(int** intervals, int intervalsSize, int* intervalsColSize, int* returnSize, int** returnColumnSizes){
    g_intervals = intervals;
    g_intervalsSize = intervalsSize;
    qsort(g_intervals, g_intervalsSize, sizeof(int*), qSortCompare);
    
    g_returnSize = 0;
    g_returnColumnSizes = malloc(sizeof(int) * g_intervalsSize);
    if (g_returnColumnSizes == NULL) {
        return NULL;
    }

    g_returnIntervals = malloc(sizeof(int* ) * g_intervalsSize);
    if (g_returnIntervals == NULL) {
        return NULL;
    }
    
    if (intervalsSize == 0) {
        *returnSize = g_returnSize;
        *returnColumnSizes = g_returnColumnSizes;
        return g_returnIntervals;
    }
    
    addInterval(g_returnSize);
    for(int i=0; i<g_intervalsSize; i++) {
        if (g_returnIntervals[g_returnSize-1][1] >= g_intervals[i][1]) {
            continue;
        } else if (g_returnIntervals[g_returnSize-1][1] >= g_intervals[i][0]) {
            g_returnIntervals[g_returnSize-1][1] = g_intervals[i][1];
        } else {
            addInterval(i);
        }
    }

    *returnSize = g_returnSize;
    *returnColumnSizes = g_returnColumnSizes;
    return g_returnIntervals;
}