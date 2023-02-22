void swap(int *nums, int index1, int index2)
{
    if (index1 == index2)
    {
        return;
    }
    int temp = nums[index1];
    nums[index1] = nums[index2];
    nums[index2] = temp;
}

void sortColors(int *nums, int numsSize)
{
    int left = 0;
    int right = numsSize - 1;
    int current = 0;
    while (current <= right)
    {
        if (nums[current] == 0)
        {
            swap(nums, left, current);
            left++;
        }
        else if (nums[current] == 2)
        {
            swap(nums, right, current);
            right--;

            // After swapping, the current index may be a zero.
            // keep current on the same index to check again.
            current--; 
        }

        current++;
    }
}
