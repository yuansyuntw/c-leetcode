typedef struct
{
    int position;
    int speed;
    float time;
} Item;

int heapCount;
Item **minHeap;

int fleetsCount;
Item **fleets;

void heapSwap(int index1, int index2)
{
    Item *tmp = minHeap[index1];
    minHeap[index1] = minHeap[index2];
    minHeap[index2] = tmp;
}

int getParentIndex(int childIndex)
{
    return (childIndex - 1) / 2;
}

void heapUpdated(int index)
{
    int currentIndex = index;
    Item *currentItem = minHeap[currentIndex];
    int parentIndex = getParentIndex(index);
    Item *parent = minHeap[parentIndex];
    while ((currentIndex > 0) && (currentItem->position < parent->position))
    {
        heapSwap(currentIndex, parentIndex);
        currentIndex = parentIndex;
        parentIndex = getParentIndex(parentIndex);
        parent = minHeap[parentIndex];
    }
}

void heapPush(Item *item)
{
    minHeap[heapCount] = item;
    heapCount++;
    heapUpdated(heapCount - 1);
}

int getLeftIndex(int parentIndex)
{
    return parentIndex * 2 + 1;
}

int getRightIndex(int parentIndex)
{
    return parentIndex * 2 + 2;
}

void minHeapify(int index)
{
    int minPosition = minHeap[index]->position;
    int minPositionIndex = index;
    int leftIndex = getLeftIndex(index);
    int rightIndex = getRightIndex(index);
    if (leftIndex < heapCount)
    {
        Item *left = minHeap[leftIndex];
        if (left->position < minPosition)
        {
            minPosition = left->position;
            minPositionIndex = leftIndex;
        }
    }

    if (rightIndex < heapCount)
    {
        Item *right = minHeap[rightIndex];
        if (right->position < minPosition)
        {
            Item *right = minHeap[rightIndex];
            minPosition = right->position;
            minPositionIndex = rightIndex;
        }
    }

    if (minPositionIndex != index)
    {
        heapSwap(minPositionIndex, index);
        minHeapify(minPositionIndex);
    }
}

Item *heapPop()
{
    if (heapCount == 0)
    {
        return NULL;
    }

    Item *top = minHeap[0];
    minHeap[0] = minHeap[heapCount - 1];
    heapCount--;
    minHeapify(0);

    return top;
}

float getTimeTo(int target, int position, int speed)
{
    return (float)(target - position) / (float)speed;
}

Item* fleetsPop() {
	if (fleetsCount == 0) {
		return NULL;
    }

	Item* top = fleets[fleetsCount - 1];
	fleetsCount--;
	return top;
}

Item* fleetsGetTop() {
	if (fleetsCount == 0) {
		return NULL;
    }

    return fleets[fleetsCount-1];
}

void fleetsPush(Item* item) {
	Item* top = fleetsGetTop();
	while(top != NULL) {
        bool willBeCatchedUp = (item->time >= top->time);
        if (willBeCatchedUp) {
            top = fleetsPop();
            if (top != NULL) { free(top); }
        } else {
            break;
        }

        top = fleetsGetTop();
    }	

    fleets[fleetsCount++] = item;
}


int carFleet(int target, int *position, int positionSize, int *speed, int speedSize)
{
    heapCount = 0;
    minHeap = (Item **)calloc(positionSize, sizeof(Item *));
    for (int i = 0; i < positionSize; i++)
    {
        Item *item = (Item *)calloc(1, sizeof(Item));
        item->position = position[i];
        item->speed = speed[i];
        item->time = getTimeTo(target, item->position, item->speed);
        heapPush(item);
    }

    fleetsCount = 0;
    fleets = (Item **)calloc(positionSize, sizeof(Item *));
    for (int i = 0; i < positionSize; i++)
    {
        Item *top = heapPop();
        if (top == NULL)
        {
            printf("heap empty, something wrong\n");
            break;
        }

        bool isFirst = (fleetsCount == 0);
        if (isFirst)
        {
            fleetsPush(top);
            continue;
        }

        fleetsPush(top);
    }

    for (int i = 0; i < heapCount; i++)
    {
        free(minHeap[i]);
    }

    for (int i = 0; i < fleetsCount; i++)
    {
        free(fleets[i]);
    }

    return fleetsCount;
}