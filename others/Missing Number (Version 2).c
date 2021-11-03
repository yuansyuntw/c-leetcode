int missingNumber(int* nums, int numsSize){
    int sum = 0;
    int expectedSum = 0;
    
    for (int i=0;i<numsSize;i++) {
        expectedSum += i;
        sum += nums[i];
    }
    
    expectedSum += numsSize;
    
    return expectedSum - sum;
}