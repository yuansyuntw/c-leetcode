int rob(int* nums, int numsSize){
    if (numsSize == 1) {
        return nums[0];
    }
    
    int forwardTwoHousesSum = nums[0];
    int forwardOneHouseSum = nums[1] > nums[0] ? nums[1] : nums[0];
    for (int i = 2; i <= numsSize-1; i++) {
        int robIHouseSum = nums[i] + forwardTwoHousesSum;
        int notRobIHouseSum = forwardOneHouseSum;
        
        forwardTwoHousesSum = forwardOneHouseSum;
        if (robIHouseSum > notRobIHouseSum) {
            forwardOneHouseSum = robIHouseSum;
        } else {
            forwardOneHouseSum = notRobIHouseSum;
        }
    }
    
    return forwardOneHouseSum;
}