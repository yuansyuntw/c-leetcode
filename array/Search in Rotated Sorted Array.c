
int *g_nums;
int g_numsSize;

int g_k;

int getValue(int index) {
    int newIndex = (index + g_k)%g_numsSize;
    return g_nums[newIndex];
}

int findPivotIndex(int startIndex, int endIndex) {
    if (startIndex > endIndex) {
        return -1;
    }
    
    if (startIndex == endIndex) {
        return endIndex;
    }
    
    int middleIndex = (startIndex + endIndex)/2;
    
    // The left element should be more than the right element.
    // When the left element is more than the right, it is the pivot element.
    if ((middleIndex < endIndex) && (g_nums[middleIndex] > g_nums[middleIndex + 1])) {
        return middleIndex;
    }
    
    if ((middleIndex > startIndex) && (g_nums[middleIndex] < g_nums[middleIndex - 1])) {
        return middleIndex - 1;
    }
    
    // the pivot element is on the left side.
    if (g_nums[startIndex] >= g_nums[middleIndex]) {
        return findPivotIndex(startIndex, middleIndex - 1);
    }
    
    return findPivotIndex(middleIndex + 1, endIndex);
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
    
    int pivotIndex = findPivotIndex(0, g_numsSize - 1);
    g_k = pivotIndex + 1;

    int foundIndex = findTargetIndex(target, 0, g_numsSize-1);
    if (foundIndex != -1) {
        foundIndex = (foundIndex + g_k) % g_numsSize;
    }
    
    return foundIndex;
}