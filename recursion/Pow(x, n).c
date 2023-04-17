double helper(double x, int n)
{
    if (x == 0)
    {
        return 0;
    }
    if (n == 0)
    {
        return 1;
    }
    if (x == 1)
    {
        return 1;
    }
    if (x == -1)
    {
        if (n % 2 == 0)
        {
            return 1;
        }
        else
        {
            return -1;
        }
    }

    double result = helper(x, n / 2);
    if (n % 2 == 0)
    {
        result = result * result;
    }
    else
    {
        result = x * result * result;
    }

    return result;
}

double myPow(double x, int n)
{
    if (n < 0)
    {
        return 1 / helper(x, n);
    }

    return helper(x, n);
}
