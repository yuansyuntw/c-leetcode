int majorityElement(int* nums, int numsSize){
    int candidate = nums[0];
    int showCount = 1;
    
    for (int i=1;i<numsSize;i++) {
        if (nums[i] == candidate) {
            showCount++;
        } else {
            if (showCount > 0) {
                showCount--;
            } else {
                candidate = nums[i];
                showCount++;
            }
        }
        
        if (showCount > floor(numsSize/2)) {
            break;
        }
    }
    
    return candidate;
}