int pivotIndex(int *nums, int numsSize)
{
    int rightSum = 0;
    int leftSum = 0;

    for (int i = 0; i < numsSize; i++)
    {
        rightSum += nums[i];
    }

    for (int i = 0; i < numsSize; i++)
    {
        if (i > 0)
        {
            leftSum += nums[i - 1];
        }

        rightSum -= nums[i];

        if (leftSum == rightSum)
        {
            return i;
        }
    }

    return -1;
}
