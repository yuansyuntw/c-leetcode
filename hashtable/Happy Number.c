const int hashtableSize = 729 + 1;
int *wasSeenHashtable;

bool isHappy(int n)
{
    bool result = false;

    wasSeenHashtable = (int *)calloc(hashtableSize, sizeof(int));

    int currentN = n;
    while (true)
    {
        bool isHappyNumber = (currentN == 1);
        if (isHappyNumber)
        {
            result = true;
            break;
        }

        bool shouldSkip = (currentN < hashtableSize);
        if (shouldSkip)
        {
            bool wasSeen = wasSeenHashtable[currentN];
            if (wasSeen)
            {
                result = false;
                break;
            }

            wasSeenHashtable[currentN] = 1;
        }

        int nextN = 0;
        int tempN = currentN;
        while (tempN > 0)
        {
            int digit = tempN % 10;
            tempN = tempN / 10;
            nextN += digit * digit;
        }
        currentN = nextN;
    }

    free(wasSeenHashtable);
    return result;
}
