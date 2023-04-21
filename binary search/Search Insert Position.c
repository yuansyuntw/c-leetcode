int searchInsert(int *nums, int numsSize, int target)
{
    int left = 0;
    int right = numsSize - 1;

    while (left <= right) // Make sure the left and the right reach each other.
    {
        int middle = (left + right) / 2;
        if (nums[middle] == target)
        {
            return middle;
        }
        else if (nums[middle] < target)
        {
            left = middle + 1;
        }
        else
        {
            right = middle - 1;
        }
    }

    return left; // If right < left, we return left. if left > right, we return left.
}
