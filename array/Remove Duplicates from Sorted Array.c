int removeDuplicates(int* nums, int numsSize){
    int checkedIndex = 0;
    
    if (numsSize > 0 ) {
        checkedIndex ++;
    }
    
    for (int forwardIndex=0; forwardIndex<numsSize; forwardIndex++) {
        printf("forward: %d, ", nums[forwardIndex]);
        bool duplicatedFlag = false;
        int duplicatedIndex = -1;
        for (int checkDuplicateIndex=0; checkDuplicateIndex < checkedIndex; checkDuplicateIndex++) {
            if (nums[checkDuplicateIndex] == nums[forwardIndex]) {
                duplicatedFlag = true;
                duplicatedIndex = checkDuplicateIndex;
                break;
            }
        }
        
        if (duplicatedFlag == false) {
            int temp = nums[checkedIndex];
            nums[checkedIndex] = nums[forwardIndex];
            nums[forwardIndex] = temp;
            checkedIndex++;
        }
    } 
    
    return checkedIndex;
}