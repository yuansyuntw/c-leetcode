// 1. Find the max number of piles and the sum of bananas
// 2. Find the k

int minEatingSpeed(int *piles, int pilesSize, int h)
{
    int max = 0;
    long sum = 0;
    for (int i = 0; i < pilesSize; i++)
    {
        sum += piles[i];
        if (piles[i] > max)
        {
            max = piles[i];
        }
    }

    if (pilesSize == h)
    {
        return max;
    }

    int left = 1;
    int right = max;
    int minK = max;
    while (left <= right)
    {
        int k = (left + right) / 2;
        if (k == minK)
        {
            break;
        }

        long hours = 0;
        for (int i = 0; i < pilesSize; i++)
        {
            if (piles[i] % k == 0)
            {
                hours += piles[i] / k;
            }
            else
            {
                hours += (piles[i] / k) + 1;
            }
        }
        if (hours <= h)
        {
            if (k < minK)
            {
                minK = k;
            }
            // try to find the mini k.
            right = k - 1;
        }
        else if (hours > h)
        {
            // too slow.
            left = k + 1;
        }
    }

    return minK;
}
