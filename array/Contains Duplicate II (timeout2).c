typedef struct {
    int value;
    int lastIndex;
} Node;


int getIndex(Node* valueToIndexArray, int valueToIndexArraySize, int value) {
    if (valueToIndexArray == NULL) {
        printf("fail to get index: not initlize the value to index array\n");
        return -1;
    }
    
    int postiveKey = value + 1000000000;
    int startKey = postiveKey/1000000000;
    
    // from startKey index
    for (int i=startKey; i<valueToIndexArraySize; i++) {
        if ((valueToIndexArray[i].lastIndex == -1) || ((valueToIndexArray[i].value == value))) {
            return i;
        }
    }
    
    // from loop to zero index
    for (int i=0; i<startKey; i++) {
        if ((valueToIndexArray[i].lastIndex == -1) || ((valueToIndexArray[i].value == value))) {
            return i;
        }
    }
    
    printf("fail to get index: not enough space\n");
    
    return -1;
}

bool saveIndex(Node* valueToIndexArray, int valueToIndexArraySize, int value, int savedIndex) {
    int index = getIndex(valueToIndexArray, valueToIndexArraySize, value);
    
    if (index == -1) {
        return false;
    }
    
    valueToIndexArray[index].value = value;
    valueToIndexArray[index].lastIndex = savedIndex;
    
    return true;
}



bool containsNearbyDuplicate(int* nums, int numsSize, int k){
    if (numsSize == 1) {
        return false;
    }
    
    bool isDuplicated = false;
    
    Node *valueToIndexArray = (Node *)malloc(sizeof(Node) * numsSize * 2);
    for (int i=0; i<numsSize*2; i++) {
        valueToIndexArray[i].value = 0;
        valueToIndexArray[i].lastIndex = -1;
    }
    
    for (int i=0; i<numsSize; i++) {
        int value = nums[i];
        int index = getIndex(valueToIndexArray, numsSize, value);
        int savedIndex = valueToIndexArray[index].lastIndex;
        if (savedIndex != -1) {
            if (abs(i - savedIndex) <= k) {
                isDuplicated = true;
                break;
            }
        }
            
        saveIndex(valueToIndexArray, numsSize, value, i);
    }
    
    free(valueToIndexArray);
    return isDuplicated;
}