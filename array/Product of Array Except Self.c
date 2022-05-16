/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
int* productExceptSelf(int* nums, int numsSize, int* returnSize){
    *returnSize = numsSize;
    int* returnArray = calloc(sizeof(int), numsSize);
    
    returnArray[0] = nums[0];
    for (int i=1;i<numsSize;i++) {
        returnArray[i] = returnArray[i-1] * nums[i];
    }
    
    returnArray[numsSize-1] = returnArray[numsSize-2];
    int postfix = nums[numsSize-1];
    for (int i=numsSize-2;i>0;i--) {
        int prefix = returnArray[i-1];
        returnArray[i] = prefix * postfix;
        postfix = postfix * nums[i];
    }
    
    returnArray[0] = postfix;
    
    return returnArray;
}