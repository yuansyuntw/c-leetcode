
int subArrayMaxSum(int* nums, int startIndex, int endIndex) {
    if (startIndex >= endIndex) {
        return nums[startIndex];
    }
    
    int middleIndex = (startIndex + endIndex)/2;
    int leftArrayMaxSum = subArrayMaxSum(nums, startIndex, middleIndex);
    int rightArrayMaxSum = subArrayMaxSum(nums, middleIndex + 1, endIndex);

    // Calculate the sum which may contain the middle element
    int sumContainedMiddle = nums[middleIndex];
    int maxSumContainedMiddle = sumContainedMiddle;
    for(int i = middleIndex-1; i>=startIndex; i--) {
        sumContainedMiddle += nums[i];
        if (sumContainedMiddle > maxSumContainedMiddle) {
            maxSumContainedMiddle = sumContainedMiddle;
        }
    }
    
    // Start the sum from it which is the max sum in the left array
    sumContainedMiddle = maxSumContainedMiddle;
    for (int i = middleIndex+1; i<=endIndex; i++) {
        sumContainedMiddle += nums[i];
        if (sumContainedMiddle > maxSumContainedMiddle) {
            maxSumContainedMiddle = sumContainedMiddle;
        }
    }

    int maxSum = leftArrayMaxSum;
    if (rightArrayMaxSum > maxSum) {
        maxSum = rightArrayMaxSum;
    }
    
    if (maxSumContainedMiddle > maxSum) {
        maxSum = maxSumContainedMiddle;
    }
    
    return maxSum;
}

int maxSubArray(int* nums, int numsSize){
    return subArrayMaxSum(nums, 0, numsSize - 1);
}