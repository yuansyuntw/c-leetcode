int singleNumber(int* nums, int numsSize){
    int singleIndex;
        
    for (int i=0; i<numsSize; i++) {
        singleIndex = -1;
        
        for (int j=0; j<numsSize; j++) {
            if (j == i) {
                continue;
            }
            
            if (nums[j] == nums[i]) {
                singleIndex = j;
                break;
            }
        }
        
        if (singleIndex == -1) {
            singleIndex = i;
            break;
        }
    }

    return nums[singleIndex];
}