void moveZeroes(int* nums, int numsSize){
    for (int i=0; i<numsSize; i++) {
        if (nums[i] != 0) {
            continue;
        }
        
        bool foundNonZeroNumner = false;
        for(int j=i+1;j<numsSize;j++) {
            if (nums[j] != 0) {
                nums[i] = nums[j];
                nums[j] = 0;
                foundNonZeroNumner = true;
                break;
            }
        }
        
        if (!foundNonZeroNumner) {
            break;
        }
    }
}