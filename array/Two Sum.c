int* twoSum(int* nums, int numsSize, int target, int* returnSize) {
    int index1;
    int index2;
    
    int sumValue;
    for (index1=0; index1<numsSize; index1++) {
        sumValue = nums[index1];
        
        if (sumValue == target) {
            *returnSize = 1;
            printf("index1: %d\n", index1);
        }
        
        for (index2=0; index2<numsSize; index2++) {
            if (index2 == index1) {
                continue;
            }
            
            if ((sumValue + nums[index2]) == target) {
                sumValue = target;
                *returnSize = 2;
                printf("index1: %d, index2:%d\n", index1, index2);
                break;
            }
        }
        
        if (sumValue == target) {
            break;
        }
    }
    
    int *returnArray = (int *)malloc(*returnSize * sizeof(int));
    
    returnArray[0] = index1;                                
    if (*returnSize == 2) {
        returnArray[1] = index2;
    } 
    
    return returnArray;
}