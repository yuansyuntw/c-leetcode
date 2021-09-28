

void merge(int* nums1, int nums1Size, int m, int* nums2, int nums2Size, int n){
    if (n == 0) {
        return;
    }
    
    for (int i=m-1; i>=0; i--) {
        nums1[i + n] = nums1[i];
    }

    int mergedIndex = 0;
    int nums1Index = n;
    int nums1CheckedCount = 0;
    int nums2Index = 0;
    int nums2CheckedCount = 0;
    
    while(mergedIndex < nums1Size) {
        if (nums1CheckedCount >= m) {
            nums1[mergedIndex++] = nums2[nums2Index++];
            nums2CheckedCount++;
            continue;
        }
        
        if (nums2CheckedCount >= n) {
            nums1[mergedIndex++] = nums1[nums1Index++];
            nums1CheckedCount++;
            continue;
        }
        
        if (nums1[nums1Index] < nums2[nums2Index]) {
            nums1[mergedIndex++] = nums1[nums1Index++];
            nums1CheckedCount++;
        } else {
            nums1[mergedIndex++] = nums2[nums2Index++];
            nums2CheckedCount++;
        }
    }
}