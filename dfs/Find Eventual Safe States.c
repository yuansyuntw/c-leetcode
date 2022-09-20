int* nodes;

int STATE_NOTSEEN = 0;
int STATE_SAFE = 1;
int STATE_NOTSAFE = 2;

void dfs(int** graph, int graphSize, int* graphColSize, int targetNode) {
    bool hadSeen = (nodes[targetNode] != STATE_NOTSEEN);
    if (hadSeen) {
        return;
    }
    
    nodes[targetNode] = STATE_NOTSAFE;
    
    int childCount = graphColSize[targetNode];
    for (int i=0; i<childCount; i++) {
        int child = graph[targetNode][i];
        dfs(graph, graphSize, graphColSize, child);
        bool isNotSafeNode = (nodes[child] == STATE_NOTSAFE);
        if (isNotSafeNode) {
            return;
        }
    }
    
    nodes[targetNode] = STATE_SAFE;
}

/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
int* eventualSafeNodes(int** graph, int graphSize, int* graphColSize, int* returnSize){
    nodes = calloc(graphSize, sizeof(int));

    int resultSize = 0;
    int* resultNodes = calloc(graphSize, sizeof(int));
    for (int n=0; n<graphSize; n++) {
        dfs(graph, graphSize, graphColSize, n);
        bool isSafeNode = (nodes[n] == STATE_SAFE);
        if (isSafeNode) {
            resultNodes[resultSize++] = n;
        }
    }
    
    free(nodes);
    
    (*returnSize) = resultSize;
    return resultNodes;
}