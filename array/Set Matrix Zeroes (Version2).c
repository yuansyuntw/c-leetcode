
struct Item {
    int row;
    int col;
    struct Item* nextItem;
};


struct Item** g_hashTable;
int g_hashTableSize;
int g_itemCount;
int g_maxItemCount;

int** g_matrix;
int g_matrixSize;
int g_matrixColSize;

int getHashCode(int row, int col) {
    int sum = col + row*10;
    return sum;
}

struct Item* getItem(int row, int col) {
    int hashCode = getHashCode(col, row);
    int index = hashCode%g_hashTableSize;
    
    struct Item* item = g_hashTable[index];
    while(item != NULL) {
        if ((item->row == row) && (item->col == col)) return item;
        item = item->nextItem;
    }
    
    return NULL;
}

struct Item* addItem(int row, int col) {
    int hashCode = getHashCode(col, row);
    
    int index = hashCode%g_hashTableSize;
    
    struct Item* item = g_hashTable[index];
    struct Item* lastItem = NULL;
    while(item != NULL) {
        if ((item->col == col) && (item->row == row)) {
            return item;
        }
        
        lastItem = item;
        item = item->nextItem;
    }
    
    struct Item* newItem = malloc(sizeof(struct Item) * 1);
    if(newItem == NULL) {
        return NULL;
    }
    
    newItem->col = col;
    newItem->row = row;
    newItem->nextItem = NULL;
    
    if (lastItem == NULL) {
        g_hashTable[index] = newItem;
    } else {
        lastItem->nextItem = newItem;
    }
    
    g_itemCount++;
    
    return newItem;
}

void makeAllToZeros(int row, int col) {
    for (int r=0; r<g_matrixSize; r++) {
        if(g_matrix[r][col] != 0) {
            g_matrix[r][col] = 0;
            addItem(r, col);
            if (g_itemCount == g_maxItemCount) return;
        }
    }

    for (int c=0; c<g_matrixColSize; c++) {
        if(g_matrix[row][c] != 0) {
            g_matrix[row][c] = 0;
            addItem(row, c);
            if (g_itemCount == g_maxItemCount) return;
        }
    }
}

void setZeroes(int** matrix, int matrixSize, int* matrixColSize){
    g_matrix = matrix;
    g_matrixSize = matrixSize;
    g_matrixColSize = *matrixColSize;
    
    g_maxItemCount = matrixSize * (*matrixColSize);
    
    g_itemCount = 0;
    g_hashTableSize = 1024;
    g_hashTable = malloc(sizeof(struct Item*) * g_hashTableSize);
    if (g_hashTable == NULL) {
        return;
    }
    
    for(int i=0;i<g_hashTableSize;i++) {
        g_hashTable[i] = NULL;
    }
    
    for (int row=0; row<matrixSize; row++) {
        for (int col=0; col<(*matrixColSize); col++) {
            struct Item* item = getItem(row, col);
            if (item == NULL) {
                if (matrix[row][col] == 0) {
                    makeAllToZeros(row, col);
                    if (g_itemCount == g_maxItemCount) break;
                    
                    // Jump to next row
                    continue;
                } else {
                    addItem(row, col);
                    if (g_itemCount == g_maxItemCount) break;
                }
            }
        }
        
        if (g_itemCount == g_maxItemCount) break;
    }
    
    for (int i=0;i<g_hashTableSize;i++) {
        struct Item* item = g_hashTable[i];
        while(item != NULL) {
            struct Item* nextItem = item->nextItem;
            free(item);
            item = nextItem;
        }
    }
    free(g_hashTable);

    return matrix;
}