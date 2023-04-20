struct Item
{
    int x;
    int y;
    float distance;
};

struct Item **heap;
int heapSize;
int heapCount;

int getLeftIndex(int nodeIndex)
{
    return 2 * nodeIndex + 1;
}

int getRightIndex(int nodeIndex)
{
    return 2 * nodeIndex + 2;
}

int getParentIndex(int nodeIndex)
{
    return (nodeIndex - 1) / 2;
}

struct Item *getItem(int index)
{
    if ((index >= 0) && (index < heapCount))
    {
        return heap[index];
    }

    return NULL;
}

void swapItems(int left, int right)
{
    struct Item *temp = heap[left];
    heap[left] = heap[right];
    heap[right] = temp;
}

void minHeapify(int index)
{
    struct Item *node = getItem(index);
    if (node == NULL)
    {
        return;
    }

    int minIndex = index;
    float minDistance = node->distance;
    int leftIndex = getLeftIndex(index);
    struct Item *left = getItem(leftIndex);
    if (left != NULL)
    {
        if (left->distance < minDistance)
        {
            minIndex = leftIndex;
            minDistance = left->distance;
        }
    }
    int rightIndex = getRightIndex(index);
    struct Item *right = getItem(rightIndex);
    if (right != NULL)
    {
        if (right->distance < minDistance)
        {
            minIndex = rightIndex;
            minDistance = right->distance;
        }
    }

    if (minIndex != index)
    {
        swapItems(index, minIndex);
        minHeapify(minIndex);
    }
}

struct Item *pop()
{
    if (heapCount == 0)
    {
        return NULL;
    }
    struct Item *result = heap[0];

    heap[0] = heap[--heapCount];
    minHeapify(0);
    return result;
}

float getDistance(struct Item *item)
{
    return (float)pow(pow(item->x, 2) + pow(item->y, 2), 0.5);
}

/**
 * Return an array of arrays of size *returnSize.
 * The sizes of the arrays are returned as *returnColumnSizes array.
 * Note: Both returned array and *columnSizes array must be malloced, assume caller calls free().
 */
int **kClosest(int **points, int pointsSize, int *pointsColSize, int k, int *returnSize, int **returnColumnSizes)
{
    heapSize = pointsSize;
    heapCount = 0;
    heap = (struct Item **)calloc(heapSize, sizeof(struct Item *));

    for (int i = 0; i < pointsSize; i++)
    {
        struct Item *newItem = (struct Item *)calloc(1, sizeof(struct Item));
        newItem->x = points[i][0];
        newItem->y = points[i][1];
        newItem->distance = getDistance(newItem);

        // We avoid inserting into the heap to speed up the process.
        // If we insert it into the heap here, it will take O(nlong) time.
        heap[heapCount++] = newItem;
    }

    // We build the min heap here, it takes O(hlogn) time. `h` is half of the node size.
    for (int i = heapCount / 2; i >= 0; i--)
    {
        minHeapify(i);
    }

    int **result = (int **)calloc(k, sizeof(int *));
    int *cols = (int *)calloc(k, sizeof(int));
    for (int i = 0; i < k; i++)
    {
        // Here only take the O(klogn) time.
        struct Item *min = pop();
        if (min == NULL)
        {
            break;
        }

        int *points = (int *)calloc(2, sizeof(int));
        points[0] = min->x;
        points[1] = min->y;
        result[i] = points;
        free(min);
        cols[i] = 2;
    }

    for (int i = 0; i < heapCount; i++)
    {
        free(heap[i]);
    }
    free(heap);

    *returnColumnSizes = cols;
    *returnSize = k;
    return result;
}
