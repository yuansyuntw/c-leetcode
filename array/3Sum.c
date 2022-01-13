int* gNums;
int gNumsSize;

int compare(void *value1, void *value2) {
    return *(int *)value1 - *(int *)value2;
}

/**
 * Return an array of arrays of size *returnSize.
 * The sizes of the arrays are returned as *returnColumnSizes array.
 * Note: Both returned array and *columnSizes array must be malloced, assume caller calls free().
 */
int** threeSum(int* nums, int numsSize, int* returnSize, int** returnColumnSizes){
    gNums = nums;
    gNumsSize = numsSize;
    
    qsort(nums, numsSize, sizeof(int), compare);
    
    int maxSize = 3000;
    int columnSize = 3;
    int **results = (int **)malloc(sizeof(int *) * maxSize);
    *returnColumnSizes = (int *)malloc(sizeof(int) * maxSize);
    
    *returnSize = 0;
    for (int i=0; i<gNumsSize-2; i++) {
        if (gNums[i] > 0) {
            break;
        }
            
        if ((i > 0) && (gNums[i] == gNums[i-1])) {
            continue;
        }
        
        int leftIndex = i+1;
        int rightIndex= gNumsSize-1;
        
        while(leftIndex < rightIndex) {
            while(leftIndex<rightIndex) {
                if ((leftIndex == i+1) || (gNums[leftIndex] != gNums[leftIndex - 1])) {
                    break;
                }
                
                leftIndex++;
            }
            
            while(leftIndex<rightIndex) {
                if ((rightIndex == gNumsSize-1) || (gNums[rightIndex + 1] != gNums[rightIndex])) {
                    break;
                }
                
                rightIndex--;
            }
            
            if (leftIndex >= rightIndex) {
                break;
            }
            
            if ((gNums[i] + gNums[leftIndex] + gNums[rightIndex]) == 0) {
                results[*returnSize] = calloc(sizeof(int), columnSize);
                (*returnColumnSizes)[*returnSize] = columnSize;
                results[*returnSize][0] = gNums[i];
                results[*returnSize][1] = gNums[leftIndex];
                results[*returnSize][2] = gNums[rightIndex];
                *returnSize = *returnSize + 1;
                
                // insufficient space for results
                if (*returnSize == maxSize) {
                    maxSize = maxSize *2;
                    results = (int **)realloc(results, sizeof(int *) * maxSize);
                    *returnColumnSizes = (int *)realloc(*returnColumnSizes, sizeof(int) * maxSize);
                }
                
                leftIndex++;
                rightIndex--;
            } else {
                int target = 0 - gNums[i];
                if (gNums[leftIndex] + gNums[rightIndex] < target) {
                    leftIndex++;
                } else {
                    rightIndex--;
                }
            }
        }
    }
    
    return results;
}