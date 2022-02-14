bool canJump(int* nums, int numsSize){
    int minCanJumpIndex = numsSize-1;
    for (int i=numsSize-2;i>=0;i--) {
        if (i + nums[i] >= minCanJumpIndex) {
            minCanJumpIndex = i;
        }
    }
    
    if (nums[0] >= minCanJumpIndex) {
        return true;
    }
    
    return false;
}