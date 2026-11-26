
#include <stdio.h>

int finalBalance(int trans[], int n, int balance)
{
    if(n == 0)
    {
        return balance;
    }
    else
    {
        balance = balance + trans[0];
        return finalBalance(trans + 1, n - 1, balance);
    }
}

int totalDeposits(int trans[], int n)
{
    if(n == 0)
    {
        return 0;
    }

    if(trans[0] > 0)
    {
        return trans[0] + totalDeposits(trans + 1, n - 1);
    }

    return totalDeposits(trans + 1, n - 1);
}

int copyLarge(int trans[], int i, int n, int large[], int k)
{
    if(i == n)
    {
        return k;
    }

    if(trans[i] <= -10000)
    {
        large[k] = trans[i];
        return copyLarge(trans, i + 1, n, large, k + 1);
    }

    return copyLarge(trans, i + 1, n, large, k);
}

int main()
{
    int balance = 20000;
    int trans[7] = {+20000, -5000, -12000, +8000, -25000, -2500, +15000};
    int large[7];

    int final = finalBalance(trans, 7, balance);
    int deposits = totalDeposits(trans, 7);
    int count = copyLarge(trans, 0, 7, large, 0);

    printf("Final balance: %d\n", final);
    printf("Total deposits: %d\n", deposits);

    printf("Large withdrawals (%d): ", count);

    for(int i = 0; i < count; i++)
    {
        printf("%d ", large[i]);
    }

    return 0;
}

