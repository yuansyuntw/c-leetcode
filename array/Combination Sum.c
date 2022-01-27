int *g_candidates;
int g_candidatesSize;
int g_target;

int** g_combinations;
int g_returnSize;
int* g_returnColumnSizes;

int compare(void *a, void *b) {
    return *(int *)a - *(int *)b;
}

void addToCombinations(int *testArray, int testArraySize) {
    int *copyTestArray = malloc(sizeof(int) * testArraySize);
    memcpy(copyTestArray, testArray, sizeof(int) * testArraySize);
    g_returnColumnSizes[g_returnSize] = testArraySize;
    g_combinations[g_returnSize] = copyTestArray;
    g_returnSize++;
}

void solve(int startCandidateIndex, int* testArray, int testArraySize, int testArraySum) {   
    for (int i = startCandidateIndex; i < g_candidatesSize; i++) {
        int sum = g_candidates[i] + testArraySum;
        
        // constraint
        if (sum <= g_target) {
            // copy a test array
            int *copyTestArray = malloc(sizeof(int) * (testArraySize + 1));
            int copyArraySize = testArraySize;
            memcpy(copyTestArray, testArray, sizeof(int) * copyArraySize);
            copyTestArray[copyArraySize++] = g_candidates[i];
            if (sum == g_target) {
                addToCombinations(copyTestArray, copyArraySize);
            } else if (sum < g_target) {
                // find the next combinations
                solve(i, copyTestArray, copyArraySize, sum);
            }
            
            // find next candidates
            free(copyTestArray);
        }
    }
}


/**
 * Return an array of arrays of size *returnSize.
 * The sizes of the arrays are returned as *returnColumnSizes array.
 * Note: Both returned array and *columnSizes array must be malloced, assume caller calls free().
 */
int** combinationSum(int* candidates, int candidatesSize, int target, int* returnSize, int** returnColumnSizes){
    // Make sure the order of candidates is ascending.
    // When we selected the candidates in solve() method, we can get an equal value or larger value.
    qsort(candidates, candidatesSize, sizeof(int), compare);
    
    g_candidates = candidates;
    g_candidatesSize = candidatesSize;
    g_target = target;
    
    int maxCombinations = 300;
    g_combinations = (int **)malloc(sizeof(int *) * maxCombinations);
    g_returnSize = 0;
    g_returnColumnSizes = malloc(sizeof(int) * maxCombinations);
    
    // goal (each candidates has been selected)
    for (int i=0; i<g_candidatesSize; i++) {
        // when the candidate is repeated, we skip it
        if ((i > 0) && (g_candidates[i] == g_candidates[i-1])) {
            continue;
        }
            
        if (g_candidates[i] <= target) {
            int *testArray = malloc(sizeof(int) * 1);
            int testSize = 0;
            testArray[testSize++] = g_candidates[i];
            if (g_candidates[i] == target) {
                addToCombinations(testArray, testSize);
            } else {
                solve(i, testArray, testSize, g_candidates[i]);
            }
            
            free(testArray);
        }
    }

    *returnSize = g_returnSize;

    *returnColumnSizes = (int *)malloc(sizeof(int) * g_returnSize);
    for (int i=0;i<g_returnSize;i++) {
        (*returnColumnSizes)[i] = g_returnColumnSizes[i];
    }
    free(g_returnColumnSizes);

    return g_combinations;
}