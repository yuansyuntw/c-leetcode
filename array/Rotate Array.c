void rotate(int* nums, int numsSize, int k){
    k = k % numsSize;
    int temp;
    
    for(int i=0; i<(numsSize/2); i++) {
        temp = nums[i];
        nums[i] = nums[numsSize-i-1];
        nums[numsSize-i-1] = temp;
    }
    
    for(int i=0; i<(k/2); i++) {
        temp = nums[i];
        nums[i] = nums[k-i-1];
        nums[k-i-1] = temp;
    }   
    
    for(int i=0; i<(numsSize-k)/2; i++) {
        temp = nums[i+k];
        nums[i+k] = nums[numsSize - i - 1];
        nums[numsSize - i - 1] = temp;
    }
}