#include <stdio.h>
#include <cs50.h>
#include <string.h>
#include <ctype.h>
#include <math.h>

int count_letters(string s); // prototype
int count_words(string s); // prototype
int count_sentences(string s); // prototype

int main(void)
{
    //Taking input from user
    string text = get_string("Text: ");
    int result;

    // calculate S, L
    int W = count_words(text);

    float S = (((float) count_sentences(text) / W) * 100);
    float L = (((float) count_letters(text) / W) * 100);

    // calculate index
    float index = ((0.0588 * L) - (0.296 * S) - (15.8));
    if (index >= 1)
    {
        result = (int) round(index);
    }
    else
    {
        result = 0;
    }


    // print result
    if (result >= 1 && result <= 16)
    {
        printf("Grade %i\n", result);
    }
    else if (result < 1)
    {
        printf("Before Grade 1\n");
    }
    else
    {
        printf("Grade 16+\n");
    }

}


int count_letters(string s) // implementation
{
    //initialize counter
    int count = 0;

    //count letters
    for (int i = 0; i <= strlen(s); i++)
    {
        //count only letters
        if (islower(s[i]) || isupper(s[i]))
        {
            count++;
        }
    }
    return count;
}

int count_words(string s) // implementation
{
    //initialize counter
    int count = 1;

    //count words
    for (int i = 0; i <= strlen(s); i++)
    {
        // count after spaces
        if (s[i] == ' ')
        {
            count++;
        }
    }
    return count;
}

int count_sentences(string s) // implementation
{
    //initalize counter
    int count = 0;

    //count sentences
    for (int i = 0; i <= strlen(s); i++)
    {
        // conut after .,!,?
        if (s[i] == '?' || s[i] == '.' || s[i] == '!')
        {
            count++;
        }

    }
    return count;
}