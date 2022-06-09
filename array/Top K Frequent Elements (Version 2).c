typedef struct {
    int number;
    int count;
} Bucket;

void switchBucket(Bucket* bucketsMaxHeap, int index1, int index2) {
    Bucket tempBucket;
    tempBucket.count = bucketsMaxHeap[index1].count;
    tempBucket.number = bucketsMaxHeap[index1].number;

    bucketsMaxHeap[index1].count = bucketsMaxHeap[index2].count;
    bucketsMaxHeap[index1].number = bucketsMaxHeap[index2].number;

    bucketsMaxHeap[index2].count = tempBucket.count;
    bucketsMaxHeap[index2].number = tempBucket.number;
}

int getRightChildIndex(int parentIndex) {
    return (parentIndex * 2) + 2;
}

int getMaxHeapValue(Bucket* bucketsMaxHeap, int bucketsMaxHeapNum, int index) {
    if (index < bucketsMaxHeapNum) {
        return bucketsMaxHeap[index].count;
    }

    return -1;
}

int getLeftChildIndex(int parentIndex) {
    return (parentIndex * 2) + 1;
}

void maxHeapitfy(Bucket* bucketsMaxHeap, int bucketsMaxHeapNum, int index) {
    int parent = getMaxHeapValue(bucketsMaxHeap, bucketsMaxHeapNum, index);
    if (parent == -1) {
        return;
    }

    int maxIndex = index;
    int max = parent;

    int leftChildIndex = getLeftChildIndex(index);
    bool isHasLeftChild = (leftChildIndex < bucketsMaxHeapNum);
    if (isHasLeftChild) {
        int leftChild = getMaxHeapValue(bucketsMaxHeap, bucketsMaxHeapNum, leftChildIndex);
        if (leftChild > parent) {
            maxIndex = leftChildIndex;
            max = leftChild;
        }
    }

    int rightChildIndex = getRightChildIndex(index);
    bool isHasRightChild = (rightChildIndex < bucketsMaxHeapNum);
    if (isHasRightChild) {
        int rightChild = getMaxHeapValue(bucketsMaxHeap, bucketsMaxHeapNum, rightChildIndex);
        if (rightChild > max) {
            maxIndex = rightChildIndex;
            max = rightChild;
        }
    }

    bool isCheckingChilds = (maxIndex != index);
    if (isCheckingChilds) {
        switchBucket(bucketsMaxHeap, index, maxIndex);
        maxHeapitfy(bucketsMaxHeap, bucketsMaxHeapNum, maxIndex);
    }
}

Bucket popMaxHeap(Bucket* bucketsMaxHeap, int* bucketsMaxHeapNum) {
    Bucket top;
    top.count = -1;
    top.number = INT_MAX;

    if ((*bucketsMaxHeapNum) <= 0) {
        printf("empty\n");
        return top;
    }

    top.count = bucketsMaxHeap[0].count;
    top.number = bucketsMaxHeap[0].number;

    int lastBucketIndex = (*bucketsMaxHeapNum) - 1;
    bucketsMaxHeap[0] = bucketsMaxHeap[lastBucketIndex];
    (*bucketsMaxHeapNum)--;
    maxHeapitfy(bucketsMaxHeap, *bucketsMaxHeapNum, 0);

    return top;
}

void buildMaxHeap(Bucket* buckets, int bucketsNum) {
    for (int i = bucketsNum / 2; i >= 0; i--) {
        maxHeapitfy(buckets, bucketsNum, i);
    }
}

int getBucketIndex(Bucket* buckets, int bucketsSize, int number, int min, float range) {
    int index = 0;

    if (range != 0) {
        index = (int)((number - min) / range);
    }

    int bucketIndex = -1;
    for (int offset = 0; offset < bucketsSize; offset++) {
        bucketIndex = (index + offset) % bucketsSize;
        Bucket bucket = buckets[bucketIndex];
        if ((bucket.count == 0) || (bucket.number == number)) { 
            break;
        }
    }

    return bucketIndex;
}

int findMax(int* nums, int numsSize) {
    int max = INT_MIN;
    for (int i = 0; i < numsSize; i++) {
        if (nums[i] > max) {
            max = nums[i];
        }
    }

    return max;
}

int findMin(int* nums, int numsSize) {
    int min = INT_MAX;
    for (int i = 0; i < numsSize; i++) {
        if (nums[i] < min) {
            min = nums[i];
        }
    }

    return min;
}

/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
int* topKFrequent(int* nums, int numsSize, int k, int* returnSize) {
    int maxNum = findMax(nums, numsSize);
    int minNum = findMin(nums, numsSize);
    float range = (float)(maxNum - minNum) / numsSize;

    int bucketSize = numsSize + 1;
    Bucket* buckets = (Bucket *)calloc(sizeof(Bucket), bucketSize);
    if (buckets == NULL) return NULL;

    int heapSize = 0;
    for (int i = 0; i < numsSize; i++) {
        int bucketIndex = getBucketIndex(buckets, bucketSize, nums[i], minNum, range);
        if (bucketIndex == -1) {
            printf("The bucket size is not enought\n");
            break;
        }

        buckets[bucketIndex].number = nums[i];
        buckets[bucketIndex].count++;
        
        bool isNewNumber = (buckets[bucketIndex].count == 1);
        if (isNewNumber) {
            heapSize++;
        }
    }

    // transfer the bucket array to a max heap
    buildMaxHeap(buckets, bucketSize);

    (*returnSize) = 0;
    int* results = (int *)calloc(sizeof(int), k);
    for (int i = 0; i < k; i++) {
        Bucket top = popMaxHeap(buckets, &bucketSize);
        if (top.count <= 0) {
            break;
        }

        int currentIndex = (*returnSize);
        results[currentIndex] = top.number;
        (*returnSize)++;
    }
    
    free(buckets);

    return results;
}