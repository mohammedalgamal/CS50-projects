#include <stdio.h>
#include <cs50.h>
#include <string.h>
#include <ctype.h>
#include <math.h>

int is_valid(string s); // prototype
string cipher(string s, string key); // prototype

int main(int argc, string argv[])
{
    //check for usage
    if (argc != 2)
    {
        //message to inform the user
        printf("Usage: ./substitution key\n");
        return 1;
    }
    else
    {
        if (!is_valid(argv[1]))
        {
            return 1;
        }
        string text = get_string("plaintext: ");
        printf("ciphertext: %s\n", cipher(text, argv[1]));
        //printf("%s\n", argv[1]);
        return 0;
    }
}



int is_valid(string s)
{
    //length
    int len = strlen(s);

    //check length
    if (len != 26)
    {
        printf("Key must contain 26 characters.\n");
        return 0;
    }

    //check non alphabitic
    for (int i = 0; i < len; i++)
    {
        if (!isalpha(s[i]))
        {
            printf("Key must contain only characters.\n");
            return 0;
        }
    }

    //check for duplicates
    for (int i = 0; i < len; i++)
    {
        for (int j = 0; j < len; j++)
        {
            if (toupper(s[i]) == toupper(s[j]) && i != j)
            {
                printf("Key must contain 26 distinct characters.\n");
                return 0;
            }
        }
    }
    return 1;
}

string cipher(string s, string key)
{
    //length
    int len = strlen(s);
    string ans = s;

    //sub
    for (int i = 0; i < len; i++)
    {
        if (islower(s[i]))
        {
            //printf("%c\n", tolower(key[s[i] - 97]));
            ans[i] = tolower(key[s[i] - 97]);
        }
        else if (isupper(s[i]))
        {
            //printf("%c\n", toupper(key[s[i] - 65]));
            ans[i] = toupper(key[s[i] - 65]);
        }
        else
        {
            //printf("%c\n", s[i]);
            ans[i] = s[i];
        }
    }

    return ans;
}