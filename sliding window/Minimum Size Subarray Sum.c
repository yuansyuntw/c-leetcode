// 1. find the sub-sum greater than the target.
// 2. start sliding windows O(n)
// 4. if the sub-sum is less than the target, we move the right index.
// 5. if the left index is at the end of the list, we stop the algorithm.

int minSubArrayLen(int target, int *nums, int numsSize)
{
    int sum = 0;
    int right = 0;
    for (; right < numsSize; right++)
    {
        sum += nums[right];
        if (sum >= target)
        {
            break;
        }
    }

    if (sum < target)
    {
        return 0;
    }

    int minLength = right + 1;
    for (int left = 1; left < numsSize; left++)
    {
        sum -= nums[left - 1];

        while ((right < numsSize - 1) && (sum < target))
        {
            right++;
            sum += nums[right];
        }

        if (sum >= target)
        {
            int newLength = (right - left + 1);
            if (newLength < minLength)
            {
                minLength = newLength;
                if (minLength == 1)
                {
                    break;
                }
            }
        }
    }

    return minLength;
}
