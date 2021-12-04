
void switchNum(int* nums, int index1, int index2) {
    int temp = nums[index2];
    nums[index2] = nums[index1];
    nums[index1] = temp;
}

void quickSort(int* nums, int numsSize, int startIndex, int endIndex) {
    if (startIndex>=endIndex) {
        return;
    }
    
    int selectedValue = nums[startIndex];

    int i = startIndex, j = endIndex;
    while(i<j) {
        while (i<j) {
            if (nums[j] < selectedValue) break;
            j--;
        }
        
        while (i<j) {
            if (nums[i] > selectedValue) break;
            i++;
        }
        
        if (i<j) {
            switchNum(nums, i, j);
        }
    }
    
    switchNum(nums, startIndex, j);

    quickSort(nums, numsSize, startIndex, j - 1);
    quickSort(nums, numsSize, j + 1, endIndex);
}

int findNextNumberIndex(int* nums, int numsSize, int currentIndex) {
    int currentValue = nums[currentIndex];
    for (int i=currentIndex+1; i<numsSize; i++) {
        if (nums[i] != currentValue) {
            return i;
        }
    }
    
    return numsSize;
}


/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
int* intersection(int* nums1, int nums1Size, int* nums2, int nums2Size, int* returnSize){
    // 1. quick sort
    quickSort(nums1, nums1Size, 0, nums1Size - 1);
    quickSort(nums2, nums2Size, 0, nums2Size - 1);

    // 2. two pointers
    int nums1Index = 0;
    int nums2Index = 0;
    int returnNumsIndex = 0;
    int* returnNums = malloc(sizeof(int) * (nums1Size+nums2Size));
    while ((nums1Index<nums1Size) && (nums2Index<nums2Size)) {
        if (nums1[nums1Index] > nums2[nums2Index]) {
            nums2Index = findNextNumberIndex(nums2, nums2Size, nums2Index);
        } else if (nums1[nums1Index] < nums2[nums2Index]) {
            nums1Index = findNextNumberIndex(nums1, nums1Size, nums1Index);
        } else {
            // Same value between nums1 array and nums2 array.
            returnNums[returnNumsIndex++] = nums1[nums1Index];
            nums1Index = findNextNumberIndex(nums1, nums1Size, nums1Index);
            nums2Index = findNextNumberIndex(nums2, nums2Size, nums2Index);
        }
    }
    
    *returnSize = returnNumsIndex;
    return returnNums;
}