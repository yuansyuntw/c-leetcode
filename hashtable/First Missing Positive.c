int firstMissingPositive(int *nums, int numsSize)
{
    // 1. Convert the negative number to zero value.
    for (int i = 0; i < numsSize; i++)
    {
        if (nums[i] < 0)
        {
            nums[i] = 0;
        }
    }

    // 2. index = number - 1
    // Make a value in the array a negative to record that number exists.
    for (int i = 0; i < numsSize; i++)
    {
        int number = abs(nums[i]);
        int index = number - 1; // hash function
        if ((index >= 0) && (index < numsSize))
        {
            if (nums[index] > 0)
            {
                nums[index] = -1 * nums[index];
            }
            else if (nums[index] == 0)
            {
                nums[index] = -1 * numsSize; // edge case
            }
        }
    }

    // 3. Check each number that the number in the array is negative.
    // If the value is negative, the number exists.
    // If the value is positive, the number does not exist.
    int result = 1;
    for (int number = 1; number <= numsSize; number++)
    {
        int index = number - 1;
        if ((index >= 0) && (index < numsSize))
        {
            result = number + 1;
            bool isExist = (nums[index] < 0);
            if (!isExist)
            {
                result = number;
                break;
            }
        }
    }

    return result;
}