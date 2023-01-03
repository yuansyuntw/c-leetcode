/**
 * Forward declaration of guess API.
 * @param  num   your guess
 * @return 	     -1 if num is higher than the picked number
 *			      1 if num is lower than the picked number
 *               otherwise return 0
 * int guess(int num);
 */

int getMedian(int low, int hight)
{
    return (low + ((hight - low + 1) / 2));
}

int guessNumber(int n)
{
    int low = 1;
    int hight = n;
    int pick = getMedian(low, hight);
    int result = guess(pick);
    while (result != 0)
    {
        if (result > 0)
        {
            low = pick + 1;
        }
        else
        {
            hight = pick - 1;
        }

        pick = getMedian(low, hight);
        result = guess(pick);
    }

    return pick;
}