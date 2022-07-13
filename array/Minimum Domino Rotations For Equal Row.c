int minDominoRotations(int* tops, int topsSize, int* bottoms, int bottomsSize) {
    int dominoSize = 7;
    int* topCounts = (int*)calloc(sizeof(int), dominoSize);
    int* bottomCounts = (int*)calloc(sizeof(int), dominoSize);

    int topMaxDomino = -1;
    int bottomMaxDomino = -1;
    int topMaxCount = 0;
    int bottomMaxCount = 0;

    for (int i = 0; i < topsSize; i++) {
        int top = tops[i];
        topCounts[top]++;

        int newTopCount = topCounts[top];
        if (newTopCount > topMaxCount) {
            topMaxCount = newTopCount;
            topMaxDomino = top;
        }

        int bottom = bottoms[i];
        bottomCounts[bottom]++;

        int newBottomCount = bottomCounts[bottom];
        if (newBottomCount > bottomMaxCount) {
            bottomMaxCount = newBottomCount;
            bottomMaxDomino = bottom;
        }
    }

    bool isMayEqualTops = ((topCounts[topMaxDomino] + bottomCounts[topMaxDomino]) >= topsSize);
    bool isMayEqualBottoms = ((topCounts[bottomMaxDomino] + bottomCounts[bottomMaxDomino]) >= bottomsSize);

    free(topCounts);
    free(bottomCounts);

    bool isCanSwap = isMayEqualTops || isMayEqualBottoms;
    if (!isCanSwap) {
        return -1;
    }

    bool isCanEqualTops = isMayEqualTops;
    bool isCanEqualBottoms = isMayEqualBottoms;
    for (int i = 0; i < topsSize; i++) {
        if (isCanEqualTops && (tops[i] != topMaxDomino) && (bottoms[i] != topMaxDomino)) {
            isCanEqualTops = false;
        }

        if (isCanEqualBottoms && (bottoms[i] != bottomMaxDomino) && (tops[i] != bottomMaxDomino)) {
            isCanEqualBottoms = false;
        }

        if (!isCanEqualBottoms && !isCanEqualTops) {
            break;
        }
    }

    isCanSwap = isCanEqualTops || isCanEqualBottoms;
    if (!isCanSwap) {
        return -1;
    }

    int topsSwapCount = INT_MAX;
    if (isCanEqualTops) {
        topsSwapCount = topsSize - topMaxCount;
    }
    
    int bottomsSwapCount = INT_MAX;
    if (isCanEqualBottoms) {
        bottomsSwapCount = bottomsSize - bottomMaxCount;
    }

    int minSwapCount = (topsSwapCount < bottomsSwapCount) ? topsSwapCount : bottomsSwapCount;
    return minSwapCount;
}