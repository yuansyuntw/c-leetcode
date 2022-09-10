struct TrapItem {
    int leftIndex;
    int rightIndex;
};

struct LeftMaxHeightItem {
    int startIndex;
    int height;
};

void pushTrapItem(struct TrapItem** stack, int* topIndex, int leftIndex, int rightIndex) {
    bool isTrap = ((rightIndex - leftIndex + 1) >= 3);
    if (!isTrap) {
        return;
    }

    int insertedIndex = (*topIndex) + 1;
    for (int i = (*topIndex); i >= 0; i--) {
        struct TrapItem* topItem = stack[i];
        bool isContain = ((leftIndex <= topItem->leftIndex) && (rightIndex >= topItem->rightIndex));
        if (isContain) {
            // pop top trap item
            free(stack[i]);
            insertedIndex = i;
        }
        else {
            break;
        }
    }

    struct TrapItem* newTrap = (struct TrapItem*)calloc(1, sizeof(struct TrapItem));
    newTrap->leftIndex = leftIndex;
    newTrap->rightIndex = rightIndex;
    stack[insertedIndex] = newTrap;
    (*topIndex) = insertedIndex;
}

void addLeftMaxHegithItem(struct LeftMaxHeightItem** stack, int* topIndex, int newStartIndex, int newHeight) {
    struct LeftMaxHeightItem* newItem = (struct LeftMaxHeightItem*)calloc(1, sizeof(struct LeftMaxHeightItem));
    newItem->height = newHeight;
    newItem->startIndex = newStartIndex;
    stack[++(*topIndex)] = newItem;
}

int getWater(int* height, int heightSize, int leftIndex, int rightHeight) {
    if ((leftIndex < 0) || (leftIndex > (heightSize - 1))) {
        return 0;
    }

    if ((rightHeight < 0) || (rightHeight > (heightSize - 1))) {
        return 0;
    }

    int minHeight = height[leftIndex];
    if (height[rightHeight] < minHeight) {
        minHeight = height[rightHeight];
    }

    int result = 0;
    for (int i = leftIndex + 1; i < rightHeight; i++) {
        int water = minHeight - height[i];
        result += water;
    }

    return result;
}

int trap(int* height, int heightSize) {
    int maxTrapStackSize = heightSize / 2;
    int trapStackIndex = -1;
    struct TrapItem** trapStack = (struct TrapItem**)calloc(maxTrapStackSize, sizeof(struct TrapItem*));

    int stackTopIndex = -1;
    struct LeftMaxHeightItem** leftMaxHeightStack = (struct LeftMaxHeightItem**)calloc(heightSize, sizeof(struct LeftMaxHeightItem*));
    for (int i = 0; i < heightSize; i++) {
        int newHeight = height[i];

        bool isEmpty = (stackTopIndex == -1);
        if (isEmpty) {
            addLeftMaxHegithItem(leftMaxHeightStack, &stackTopIndex, i, newHeight);
            continue;
        }

        int leftIndex = -1;
        int rightIndex = -1;
        while (stackTopIndex >= 0) {
            struct LeftMaxHeightItem* topItem = leftMaxHeightStack[stackTopIndex];

            // Descrenning Monotonic Stack
            bool isCanPush = (newHeight <= topItem->height);
            if (isCanPush) {
                break;
            }
            else {
                // pop
                struct LeftMaxHeightItem* item = leftMaxHeightStack[stackTopIndex];
                leftIndex = item->startIndex;
                rightIndex = i;
                free(item);

                stackTopIndex--;
                if (stackTopIndex >= 0) {
                    struct LeftMaxHeightItem* topItem = leftMaxHeightStack[stackTopIndex];
                    leftIndex = topItem->startIndex;
                }
            }
        }

        bool isExistTrap = ((leftIndex != -1) && (rightIndex != -1));
        if (isExistTrap) {
            pushTrapItem(trapStack, &trapStackIndex, leftIndex, rightIndex);
        }

        addLeftMaxHegithItem(leftMaxHeightStack, &stackTopIndex, i, newHeight);
    }

    int result = 0;
    for (int i = 0; i <= trapStackIndex; i++) {
        struct TrapItem* trap = trapStack[i];

        int water = getWater(height, heightSize, trap->leftIndex, trap->rightIndex);
        result += water;

        free(trapStack[i]);
    }
    free(trapStack);

    for (int i = 0; i <= stackTopIndex; i++) {
        free(leftMaxHeightStack[i]);
    }
    free(leftMaxHeightStack);

    return result;
}