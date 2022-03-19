#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

int main(int argc, char *argv[])
{
    //check for number of cla
    if (argc != 2)
    {
        printf("Usage: ./recover IMAGE");
        return 1;
    }

    // Open input file
    FILE *file = fopen(argv[1], "r");
    if (file == NULL)
    {
        printf("Could not open %s.\n", argv[1]);
        return 1;
    }

    //byte type
    typedef uint8_t BYTE;

    //buffer for storing each block
    BYTE buffer[512];

    //count JPEGs
    int count = 0;

    //filename
    char *filename = malloc(17);

    //read from file
    while (fread(buffer, sizeof(BYTE), 512, file) == 512)
    {
        if (buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff && (buffer[3] & 0xf0) == 0xe0)
        {
            sprintf(filename, "%03i.jpg", count);
            count++;
            FILE *img = fopen(filename, "w");
            fwrite(buffer, sizeof(BYTE), 512, img);
            fclose(img);
        }
        else if (count != 0)
        {
            FILE *img = fopen(filename, "a");
            fwrite(buffer, sizeof(BYTE), 512, img);
            fclose(img);
        }

    }

    //free filename
    free(filename);
}