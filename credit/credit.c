#include <stdio.h>
#include <cs50.h>

int get_digits(long a); // prototype for getting digits
int num_digits(long c); // prototype for getting num of digits
long power(long aa, int bb); // prototype for power function

int main(void)
{
    long x;
    do
    {
        x = get_long("Enter credit card number: ");
    }
    while (!(x >= 0));
    int alg = get_digits(x);
    int num = num_digits(x);
    int pre = x / power(10, num - 2);
    if (alg == 0)
    {
        if (num == 15 && (pre == 34 || pre == 37))
        {
            printf("AMEX\n");
        }
        else if (num == 16 && pre >= 51 && pre <= 55)
        {
            printf("MASTERCARD\n");
        }
        else if ((num == 13 || num == 16) && pre / 10 == 4)
        {
            printf("VISA\n");
        }
        else
        {
            printf("INVALID\n");
        }
    }
    else
    {
        printf("INVALID\n");
    }
    //printf("%i", get_digits(x));
}

int get_digits(long a)
{
    int i = 0; // digit itself
    long j = 1; // power of 10
    int b = 1; // even digits detector
    int sum_odd = 0; // sum of odd digits
    int sum_even = 0; // sum of even digits
    int total = 0; // total of sums
    while (a / j > 0)
    {
        i = (a / j) % 10;
        if (b % 2 == 0)
        {
            i *= 2;
            sum_even += ((i % 10) + ((i / 10)  % 10));
        }
        else
        {
            sum_odd += i;
        }
        //printf("%i\n", i);
        j *= 10;
        b++;
    }
    total = (sum_even + sum_odd) % 10;
    return total;
}



int num_digits(long c)
{
    int i = 0; // digit counter
    long j = 1; // power of 10
    while (c / j > 0)
    {
        i++;
        j *= 10;
    }
    return i;
}



long power(long aa, int bb)
{
    long ans = aa;
    for (int i = 1; i < bb; i++)
    {
        ans *= aa;
    }
    return ans;

}