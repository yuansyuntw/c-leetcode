struct Node {
    struct Node* parent;
};

int gGridSize;
int gGridColSize;

int gGroupCount;
struct Node*** gNodeTable;

struct Node* getParentNode(int r, int c) {
    if ((r<0) || (r>=gGridSize) || (c<0) || (c>=gGridColSize)) {
        return NULL;
    }
    
    struct Node* node = gNodeTable[r][c];
    while ((node != NULL) && (node->parent != node)) {
        node = node->parent;
    };
    
    return node;
}

void setParent(int r, int c) {
    gNodeTable[r][c] = calloc(sizeof(struct Node), 1);
    
    struct Node* topParentNode = getParentNode(r-1, c);
    struct Node* leftParentNode = getParentNode(r, c-1);
    
    if ((topParentNode != NULL) || (leftParentNode != NULL)) {
        // union
        if ((topParentNode != NULL) && (leftParentNode != NULL) && (topParentNode != leftParentNode)) {
            leftParentNode->parent = topParentNode;
            gGroupCount--;
            
            gNodeTable[r][c]->parent = gNodeTable[r-1][c];
        } else {
            if (topParentNode != NULL) gNodeTable[r][c]->parent = gNodeTable[r-1][c];
            if (leftParentNode != NULL) gNodeTable[r][c]->parent = gNodeTable[r][c-1];
        }
    } else {
        gNodeTable[r][c]->parent = gNodeTable[r][c];
        gGroupCount++;
    }
}

int numIslands(char** grid, int gridSize, int* gridColSize){
    gGridSize = gridSize;
    gGridColSize = *gridColSize;
    gGroupCount = 0;
    
    gNodeTable = malloc(sizeof(struct Node**) * gridSize);
    for (int r=0;r<gGridSize;r++) {
        gNodeTable[r] = calloc(sizeof(struct Node*), gGridColSize);
    }
    
    for (int r=0;r<gGridSize;r++) {
        for (int c=0;c<gGridColSize;c++) {
            if (grid[r][c] == '1') {
                setParent(r, c);
            }
        }
    }
    
    for (int r=0;r<gGridSize;r++) {
        for (int c=0;c<gGridColSize;c++) {
            if (gNodeTable[r][c] != NULL) {
                free(gNodeTable[r][c]);
            }
        }
        free(gNodeTable[r]);
    }
    free(gNodeTable);
    
    return gGroupCount;
}