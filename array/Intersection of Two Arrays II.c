
int comp (const void * elem1, const void * elem2) {
    int a = *((int *) elem1);
    int b = *((int *) elem2);
    
    if (a > b) {
        return 1;
    } else if (a < b) {
        return -1;
    } else {
        return 0;
    }
}

int* intersect(int* nums1, int nums1Size, int* nums2, int nums2Size, int* returnSize){

    //1. sort 
    qsort((void *)nums1, nums1Size, sizeof(int), comp);
    qsort((void *)nums2, nums2Size, sizeof(int), comp);
    
    //2. compare    
    int *smallerNums;
    int smallerNumsSize;
    int *biggerNums;
    int biggerNumsSize;
    
    if (nums1Size > nums2Size) {
        smallerNums = nums2;
        smallerNumsSize = nums2Size;
        biggerNums = nums1;
        biggerNumsSize = nums1Size;
    } else {
        smallerNums = nums1;
        smallerNumsSize = nums1Size;
        biggerNums = nums2;
        biggerNumsSize = nums2Size;
    }

    int *intersectNums = (int *)malloc(smallerNumsSize * sizeof(int));
    
    int startIndex = 0;
    int intersectCount = 0;
    for (int i=0; i<smallerNumsSize; i++) {            
        for (int j=startIndex; j<biggerNumsSize; j++) {
            if (smallerNums[i] == biggerNums[j]) {
                intersectNums[intersectCount] = smallerNums[i];
                startIndex = j + 1;
                intersectCount ++;
                
                break; // skip the later of bigger array
            }
        }
    }

    *returnSize = intersectCount;
    return intersectNums;
}