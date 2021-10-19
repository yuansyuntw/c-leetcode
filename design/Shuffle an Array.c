typedef struct {
    int numsSize;
    int* nums;
    int* shuffleNums;
    time_t seed;
} Solution;

Solution* solutionCreate(int* nums, int numsSize) {
    Solution* newSolution = malloc(sizeof(Solution));
    
    newSolution->numsSize = numsSize;
    newSolution->nums = malloc(sizeof(int) * numsSize);
    newSolution->shuffleNums = (int*) malloc(sizeof(int) * numsSize);
    newSolution->seed = time(NULL);
    for(int i=0;i<numsSize;i++) {
        newSolution->nums[i] = nums[i];
    }
    
    return newSolution;
}

int* solutionReset(Solution* obj, int* retSize) {
    *retSize = obj->numsSize;
    memcpy(obj->shuffleNums, obj->nums, sizeof(int) * obj->numsSize);
    return obj->shuffleNums;
}

int* solutionShuffle(Solution* obj, int* retSize) {
    srand(obj->seed++);
    
    memcpy(obj->shuffleNums, obj->nums, sizeof(int) * obj->numsSize);
    for(int i=0; i<obj->numsSize; i++) {
        int shuffleIndex = rand() % obj->numsSize;
        
        int temp = obj->shuffleNums[i];
        
        // Each element will be assigned a random element
        obj->shuffleNums[i] = obj->shuffleNums[shuffleIndex];
        
        obj->shuffleNums[shuffleIndex] = temp;
    }
    
    *retSize = obj->numsSize;
    return obj->shuffleNums;
}

void solutionFree(Solution* obj) {
    free(obj->nums);
    free(obj->shuffleNums);
    free(obj);
}

/**
 * Your Solution struct will be instantiated and called as such:
 * Solution* obj = solutionCreate(nums, numsSize);
 * int* param_1 = solutionReset(obj, retSize);
 
 * int* param_2 = solutionShuffle(obj, retSize);
 
 * solutionFree(obj);
*/