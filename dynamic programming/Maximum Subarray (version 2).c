int maxSubArray(int* nums, int numsSize){
    if (numsSize == 1) {
        return nums[0];
    }
    
    int currentMaxSubArraySum = nums[0];
    int maxSum = currentMaxSubArraySum;
    for(int i=1; i<numsSize; i++) {
        int subArraySum = currentMaxSubArraySum + nums[i];
        if (subArraySum > nums[i]) {
            currentMaxSubArraySum = subArraySum;
        } else {
            currentMaxSubArraySum = nums[i];
        }
        
        if (currentMaxSubArraySum > maxSum) {
            maxSum = currentMaxSubArraySum;
        }
    }
    
    return maxSum;
}