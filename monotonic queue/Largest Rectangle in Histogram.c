struct Item
{
    int startIndex;
    int height;
};

int largestRectangleArea(int *heights, int heightsSize)
{
    int maxArea = 0;

    int stackCount = 0;
    struct Item **stack = (struct Item **)calloc(heightsSize, sizeof(struct Item *));

    for (int i = 0; i < heightsSize; i++)
    {
        int startIndex = i;
        int currentHeight = heights[i];
        for (int top = stackCount - 1; top >= 0; top--)
        {
            if (currentHeight <= stack[top]->height)
            {
                // Base on the current location to calculate the current area.
                int width = i - stack[top]->startIndex;
                int area = width * stack[top]->height;
                if (area > maxArea)
                {
                    maxArea = area;
                }

                // This represents the height that can extend to the previous location.
                startIndex = stack[top]->startIndex;
                stackCount--;
                free(stack[top]);
            }
            else
            {
                break;
            }
        }
        struct Item *newItem = (struct Item *)calloc(1, sizeof(struct Item));
        newItem->height = currentHeight;
        newItem->startIndex = startIndex;
        stack[stackCount++] = newItem;
    }

    for (int i = 0; i < stackCount; i++)
    {
        int width = heightsSize - stack[i]->startIndex;
        int area = stack[i]->height * width;
        if (area > maxArea)
        {
            maxArea = area;
        }
        free(stack[i]);
    }
    free(stack);

    return maxArea;
}