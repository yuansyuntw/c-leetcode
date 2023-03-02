bool canPartition(int *nums, int numsSize)
{
    int sum = 0;
    for (int i = 0; i < numsSize; i++)
    {
        sum += nums[i];
    }
    float target = sum / 2.0;

    if ((int)(target * 10) % 10 > 0)
    {
        return false;
    }

    int numMaxRange = 101;
    int subsumsSize = numMaxRange * numsSize;
    int *set = (int *)calloc(subsumsSize, sizeof(int));

    int *subsums = (int *)calloc(subsumsSize, sizeof(int));
    int subsumsCount = 0;

    subsums[subsumsCount++] = 0; // not include any number.

    bool result = false;
    for (int i = numsSize - 1; i >= 0; i--)
    {
        int num = nums[i];
        if (num == target)
        {
            result = true;
            break;
        }

        int currentSubsumsCount = subsumsCount;
        for (int subsumIndex = 0; subsumIndex < currentSubsumsCount; subsumIndex++)
        {
            int newSubsum = subsums[subsumIndex] + num;
            if (newSubsum == target)
            {
                result = true;
                break;
            }
            if (set[newSubsum] == 0)
            {
                set[newSubsum] = 1;
                subsums[subsumsCount++] = newSubsum;
            }
        }

        if (result)
        {
            break;
        }
    }

    free(subsums);
    free(set);

    return result;
}
