int hadSeenCount;
int* hadSeenNodes;
    
int* isSafeNodes;

void dfs(int** graph, int graphSize, int* graphColSize, int targetNode) {
    bool hadSeen = (hadSeenNodes[targetNode] == 1);
    if (hadSeen) {
        return;
    }
    
    hadSeenNodes[targetNode] = 1;
    
    int childCount = graphColSize[targetNode];
    for (int i=0; i<childCount; i++) {
        int child = graph[targetNode][i];
        dfs(graph, graphSize, graphColSize, child);
        bool isSafeNode = (isSafeNodes[child]);
        if (!isSafeNode) {
            return;
        }
    }
    
    isSafeNodes[targetNode] = 1;
}

/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
int* eventualSafeNodes(int** graph, int graphSize, int* graphColSize, int* returnSize){
    hadSeenCount = 0;
    hadSeenNodes = calloc(graphSize, sizeof(int));
    
    isSafeNodes = calloc(graphSize, sizeof(int));
    
    int resultSize = 0;
    int* resultNodes = calloc(graphSize, sizeof(int));
    
    for (int n=0; n<graphSize; n++) {
        dfs(graph, graphSize, graphColSize, n);
        bool isSafeNode = (isSafeNodes[n]);
        if (isSafeNode) {
            resultNodes[resultSize++] = n;
        }
    }
    
    free(hadSeenNodes);
    free(isSafeNodes);
    
    (*returnSize) = resultSize;
    return resultNodes;
}