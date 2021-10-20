typedef struct {
    int* elements;
    int* minElementStack;
    int elementsSize;
    int elementsMaxSize;
} MinStack;

MinStack* minStackCreate() {
    MinStack *newStack = malloc(sizeof(MinStack));
    
    newStack->elementsSize = 0;
    newStack->elementsMaxSize = 30000;
    newStack->elements = malloc(sizeof(int)*newStack->elementsMaxSize);
    newStack->minElementStack = malloc(sizeof(int)*newStack->elementsMaxSize);
    
    return newStack;
}

void minStackPush(MinStack* obj, int val) {
    obj->elements[obj->elementsSize] = val;
    
    int minElement;
    if (obj->elementsSize == 0) {
        minElement = val;
    } else {
        if (val < obj->minElementStack[obj->elementsSize-1]) {
            minElement = val;
        } else {
            minElement = obj->minElementStack[obj->elementsSize-1];
        }
    }
    
    obj->minElementStack[obj->elementsSize] = minElement;
    obj->elementsSize++;
}

void minStackPop(MinStack* obj) {
    if (obj->elementsSize > 0) {
        obj->elementsSize--;
    }
}

int minStackTop(MinStack* obj) {
    if (obj->elementsSize > 0) {
        return obj->elements[obj->elementsSize-1];
    } else {
        return -1;
    }
}

int minStackGetMin(MinStack* obj) {
    if (obj->elementsSize > 0) {
        return obj->minElementStack[obj->elementsSize-1];
    } else {
        return -1;
    }
}

void minStackFree(MinStack* obj) {
    free(obj->elements);
    free(obj->minElementStack);
    free(obj);
}

/**
 * Your MinStack struct will be instantiated and called as such:
 * MinStack* obj = minStackCreate();
 * minStackPush(obj, val);
 
 * minStackPop(obj);
 
 * int param_3 = minStackTop(obj);
 
 * int param_4 = minStackGetMin(obj);
 
 * minStackFree(obj);
*/