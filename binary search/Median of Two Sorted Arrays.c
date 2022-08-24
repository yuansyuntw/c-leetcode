int min(int a, int b) {
    if (a < b) {
        return a;
    }

    return b;
}

int max(int a, int b) {
    if (a > b) {
        return a;
    }

    return b;
}

double findMedianSortedArrays(int* nums1, int nums1Size, int* nums2, int nums2Size) {
    int totalSize = nums1Size + nums2Size;
    int halfOfTotalSize = totalSize / 2;

    int* smallerNums = nums1;
    int smallerNumsSize = nums1Size;
    int* biggerNums = nums2;
    int biggerNumsSize = nums2Size;
    if (nums2Size < nums1Size) {
        smallerNums = nums2;
        smallerNumsSize = nums2Size;
        biggerNums = nums1;
        biggerNumsSize = nums1Size;
    }

    int leftIndex = 0;
    int rightIndex = smallerNumsSize - 1;
    while (true) {
        int smallerLeftPartitionMaxIndex = (leftIndex + rightIndex) / 2;

        bool isCannotPartition = (leftIndex > rightIndex);
        if (isCannotPartition) {
            smallerLeftPartitionMaxIndex = -1;
        }

        int smallerRightPartitionMinIndex = smallerLeftPartitionMaxIndex + 1;
        int smallerLeftPartitionSize = smallerLeftPartitionMaxIndex + 1;
        
        int biggerLeftPartitionSize = halfOfTotalSize - smallerLeftPartitionSize;
        int biggerLeftPartitionMaxIndex = biggerLeftPartitionSize - 1;
        int biggerRightPartitionMinIndex = biggerLeftPartitionMaxIndex + 1;

        int smallerLeftPartitionMax = INT_MIN;
        if ((smallerNumsSize > 0) && (smallerLeftPartitionMaxIndex >= 0) && (smallerLeftPartitionMaxIndex < smallerNumsSize)) {
            smallerLeftPartitionMax = smallerNums[smallerLeftPartitionMaxIndex];
        }

        int smallerRightPartitionMin = INT_MAX;
        if ((smallerNumsSize > 0) && (smallerRightPartitionMinIndex >= 0) && (smallerRightPartitionMinIndex < smallerNumsSize)) {
            smallerRightPartitionMin = smallerNums[smallerRightPartitionMinIndex];
        }

        int biggerLeftPartitionMax = INT_MIN;
        if ((biggerNumsSize > 0) && (biggerLeftPartitionMaxIndex >= 0) && (biggerLeftPartitionMaxIndex < biggerNumsSize)) {
            biggerLeftPartitionMax = biggerNums[biggerLeftPartitionMaxIndex];
        }

        int biggerRightPartitionMin = INT_MAX;
        if ((biggerNumsSize > 0) && (biggerRightPartitionMinIndex >= 0) && (biggerRightPartitionMinIndex < biggerNumsSize)) {
            biggerRightPartitionMin = biggerNums[biggerRightPartitionMinIndex];
        }

        bool isCorrectPartition = ((smallerLeftPartitionMax <= biggerRightPartitionMin) &&
            (biggerLeftPartitionMax <= smallerRightPartitionMin));
        if (isCorrectPartition) {
            double result = min(smallerRightPartitionMin, biggerRightPartitionMin);
            bool isEven = ((totalSize % 2) == 0);
            if (isEven) {
                result = (result + max(smallerLeftPartitionMax, biggerLeftPartitionMax)) / 2.0;
            }

            return result;
        }
        else if (smallerLeftPartitionMax > biggerRightPartitionMin) {
            // too big
            rightIndex = smallerLeftPartitionMaxIndex - 1;
        }
        else {
            // too small
            leftIndex = smallerLeftPartitionMaxIndex + 1;
        }
    }

    return 0;
}