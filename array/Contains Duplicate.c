bool containsDuplicate(int* nums, int numsSize){
    for (int i=0; i<numsSize; i++) {
        for (int j=0; j<i; j++) {
            if (nums[j] == nums[i]) {
                return true;
            }
        }
    }
    
    return false;
}