

int rob(int* nums, int numsSize){
    int *sumArray = malloc(sizeof(int) * numsSize);
    int maxSumInAllNums = nums[numsSize-1];
    for (int i = numsSize-1; i>=0; i--) {
        int maxSum = nums[i];
        for (int j=i+2; j<=numsSize-1; j++) {
            if (nums[i] + sumArray[j] > maxSum) {
                maxSum = nums[i] + sumArray[j];
            }
        }
        
        sumArray[i] = maxSum;
        if (sumArray[i] > maxSumInAllNums) {
            maxSumInAllNums = sumArray[i];
        }
    }
    
    return maxSumInAllNums;
}