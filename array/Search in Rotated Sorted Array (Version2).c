int *g_nums;
int g_numsSize;

int g_k;

int getValue(int index) {
    int newIndex = (index + g_k)%g_numsSize;
    return g_nums[newIndex];
}

int findTargetIndex(int targetValue, int startIndex, int endIndex) {
    if (startIndex > endIndex) {
        return -1;
    }
    
    int middleIndex = (startIndex + endIndex)/2;
    int middleValue = getValue(middleIndex);
    
    if (middleValue < targetValue) {
        return findTargetIndex(targetValue, middleIndex + 1, endIndex);
    }
    
    if (middleValue > targetValue) {
        return findTargetIndex(targetValue, startIndex, middleIndex - 1);
    }

    return middleIndex;
}

int search(int* nums, int numsSize, int target){
    g_nums = nums;
    g_numsSize = numsSize;
    
    int minValue = nums[0];
    int minIndex = 0;
    for (int i=1;i<g_numsSize;i++) {
        if (g_nums[i] < minValue) {
            minValue = g_nums[i];
            minIndex = i;
        }
    }
    g_k = minIndex;

    int foundIndex = findTargetIndex(target, 0, g_numsSize-1);
    if (foundIndex != -1) {
        foundIndex = (foundIndex + g_k) % g_numsSize;
    }
    
    return foundIndex;
}