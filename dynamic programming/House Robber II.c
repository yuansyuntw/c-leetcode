int* gNums;
int gNumsSize;

int max(int value1, int value2) {
    return (value1 > value2) ? value1 : value2;
}

int helper(int startIndex, int endIndex) {
    int rob1 = 0;
    int rob2 = 0;
    int rob3 = 0;
    
    for (int i=startIndex;i<=endIndex;i++) {
        rob3 = max(gNums[i] + rob1, rob2);
        rob1 = rob2;
        rob2 = rob3;
    }
    
    return rob2;
}

int rob(int* nums, int numsSize){
    gNums = nums;
    gNumsSize = numsSize;
    
    int result = nums[0];
    result = max(helper(0, numsSize-2), result);
    return max(helper(1, numsSize-1), result);
}