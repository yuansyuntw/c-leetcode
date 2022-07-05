void swap(int** intervals, int intervalsSize, int intervalColSize, int index1, int index2) {
    if (index1 == index2) {
        return;
    }

    int* temp = (int*)calloc(sizeof(int), intervalColSize);
    for (int c = 0; c < intervalColSize; c++) {
        temp[c] = intervals[index1][c];
        intervals[index1][c] = intervals[index2][c];
        intervals[index2][c] = temp[c];
    }

    free(temp);
}

int partition(int** intervals, int intervalsSize, int intervalColSize, int startIndex, int endIndex) {
    int sortedBaseIndex = 0;
    
    srand(time(NULL));
    int pivotIndex = startIndex + (rand() % (endIndex - startIndex));
    swap(intervals, intervalsSize, intervalColSize, startIndex, pivotIndex);
    
    pivotIndex = startIndex;
    int pivot = intervals[pivotIndex][sortedBaseIndex];
    
    int backwardIndex = startIndex + 1;
    int forwardIndex = endIndex;
    while (true) {
        while ((forwardIndex > startIndex) && (intervals[forwardIndex][sortedBaseIndex] >= pivot)) {
            forwardIndex--;
        }
        
        while ((backwardIndex < endIndex) && (intervals[backwardIndex][sortedBaseIndex] <= pivot)) {
            backwardIndex++;
        }

        if (backwardIndex >= forwardIndex) {
            break;
        }
        
        swap(intervals, intervalsSize, intervalColSize, forwardIndex, backwardIndex);
    }

    swap(intervals, intervalsSize, intervalColSize, pivotIndex, forwardIndex);
    
    return forwardIndex;
}

void quickSort(int** intervals, int intervalsSize, int intervalColSize, int startIndex, int endIndex) {
    if (startIndex < endIndex) {
        int pivot = partition(intervals, intervalsSize, intervalColSize, startIndex, endIndex);
        quickSort(intervals, intervalsSize, intervalColSize, startIndex, pivot - 1);
        quickSort(intervals, intervalsSize, intervalColSize, pivot + 1, endIndex);
    }
}

int eraseOverlapIntervals(int** intervals, int intervalsSize, int* intervalsColSize) {
    quickSort(intervals, intervalsSize, intervalsColSize[0], 0, intervalsSize - 1);

    int result = 0;
    int firstOneIndex = 0;
    int intervalMinIndex = 0;
    int intervalMaxIndex = 1;
    int currentIntervalMax = intervals[firstOneIndex][intervalMaxIndex];
    for (int i = 1; i < intervalsSize; i++) {
        if (intervals[i][intervalMinIndex] >= currentIntervalMax) {
            currentIntervalMax = intervals[i][intervalMaxIndex];
        }
        else {
            result++;

            //Choice the smallest one to minimize the removed count
            if (intervals[i][intervalMaxIndex] < currentIntervalMax) {
                currentIntervalMax = intervals[i][intervalMaxIndex];
            }
        }
    }

    return result;
}