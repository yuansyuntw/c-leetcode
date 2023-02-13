int gNumsSize;
int *gNums;

void swap(int left, int right)
{
    int temp = gNums[left];
    gNums[left] = gNums[right];
    gNums[right] = temp;
}

int partition(int left, int right)
{
    int pivot = left;
    int max = right;
    int min = left;

    while (left < right)
    {
        while (left <= max)
        {
            if (gNums[left] > gNums[pivot])
            {
                break;
            }
            left++;
        }

        while (right >= min)
        {
            if (gNums[right] < gNums[pivot])
            {
                break;
            }
            right--;
        }

        if ((left < right) && (left <= max) && (right >= min))
        {
            swap(left, right);
        }
    }

    if (right < min)
    {
        right = pivot;
    }

    swap(pivot, right);
    return right;
}

int findKthLargest(int *nums, int numsSize, int k)
{
    gNums = nums;
    gNumsSize = numsSize;

    int left = 0;
    int right = numsSize - 1;
    int targetIndex = numsSize - k;
    while (left < right)
    {
        int index = partition(left, right);
        if (index == targetIndex)
        {
            return nums[index];
        }
        else if (index < targetIndex)
        {
            left = index + 1; // right side
        }
        else
        {
            right = index - 1; // left side
        }
    }

    return nums[left];
}
