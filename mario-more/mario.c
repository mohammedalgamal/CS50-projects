#include <stdio.h>
#include <cs50.h>

int get_height(void);    // prototype for the function that takes the height
void print_hash(int x);  // prototype for printing hashes


int main(void)
{
    int n = get_height();   // height of the blocks
    int i;
    int d;
    for (i = 1; i <= n; i++) // loop for printing functions
    {
        d = n - i; // space detector
        printf("%.*s", d, "                       "); // space printer
        print_hash(i);
        printf("  ");
        print_hash(i);
        printf("\n");
    }

}


int get_height(void) // implementation
{
    int n;
    do
    {
        n = get_int("Height: ");
    }
    while (n > 8 || n < 1); // make sure of the boundries

    return n;
}


void print_hash(int y) // implementation
{
    for (int j = y; j > 0; j--) // printing blocks
    {
        printf("#");
    }
}