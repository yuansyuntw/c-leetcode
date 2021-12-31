int* inputNums;
int intputNumsSize;

void swap(int index1, int index2) {
    int temp = inputNums[index1];
    inputNums[index1] = inputNums[index2];
    inputNums[index2] = temp;
}

void quickSort(int startIndex, int endIndex) {
    if (startIndex >= endIndex) {
        return;
    }
    
    // Random the pivot can make quick sort to O(nlon).
    srand(time(NULL));
    int randomIndex = startIndex + rand() % (endIndex-startIndex);
    swap(startIndex, randomIndex);
    
    int selectedIndex = startIndex;
    int selectedValue = inputNums[selectedIndex];
    int i=startIndex+1; // Here should be more than the selected index.
    int j=endIndex;

    // Make sure the j can enter the while-loop
    while(i<=j) {
        // When the j is equal to i, the j will same as the selected index.
        while (i<=j) {
            if (inputNums[j] < selectedValue) {
                break;
            }
            
            j--;
        }
        
        while (i<=j) {
            if (inputNums[i] > selectedValue) {
                break;
            }
            
            i++;
        }
        
        // Only swap element in the j  index greater than I index.
        if (i<j) {
            swap(i, j);
        }
    }
    
    // This j index may same as the selected index.
    swap(selectedIndex, j);
    quickSort(startIndex, j-1);
    quickSort(j+1, endIndex);
}


/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
int* sortArray(int* nums, int numsSize, int* returnSize){
    inputNums = nums;
    intputNumsSize = numsSize;
    
    quickSort(0, numsSize-1);
    
    *returnSize = numsSize;
    return inputNums;
}