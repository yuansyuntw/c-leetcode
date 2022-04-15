
int g_numsSize;
int* g_nums;

int getLeftChildIndex(int parentIndex) {
    return (parentIndex + 1) * 2 - 1;
}

int getRightChildIndex(int parentIndex) {
    return (parentIndex + 1) * 2;
}

int getMinChild(int parentIndex) {
    if (parentIndex>g_numsSize-1) return INT_MAX;
    
    int leftChildIndex = getLeftChildIndex(parentIndex);
    int rightChildIndex = getRightChildIndex(parentIndex);
    
    int parentValue = g_nums[parentIndex];
    int leftChildValue = getMinChild(leftChildIndex);
    int rightChildValue = getMinChild(rightChildIndex);
    
    // min binary heap
    int min = parentValue;
    if (leftChildValue < min) min = leftChildValue;
    if (rightChildValue < min) min = rightChildValue;
    
    return min;
}


int findMin(int* nums, int numsSize){
    g_numsSize = numsSize;
    g_nums = nums;
    return getMinChild(0);
}