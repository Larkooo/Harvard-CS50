#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

int main(int argc, char *argv[])
{
    if (argc != 2) {
        printf("One argument required : File path\n");
        return 1;
    }

    FILE* file = fopen(argv[1], "r");

    if (file == NULL)
    {
        printf("Could not open file\n");
        return 1;
    }

    // allocate 512 bytes, size of a block
    uint8_t block[512];

    // count of jpegs
    int count = 0;

    FILE* output = NULL;

    while(fread(&block, sizeof(uint8_t), 512, file))
    {
        // checking first three bytes
        if (block[0] == 0xff && block[1] == 0xd8 && block[2] == 0xff && (block[3] & 0xf0) == 0xe0)
        {
            if (output != NULL) fclose(output);
            // file named based on count
            char fileName[8];
            sprintf(fileName, "%03i.jpg", count);

            // creating output file
            output = fopen(fileName, "w");

            count++;
        }
        if (output != NULL) {
            // writing block to file
            fwrite(&block, sizeof(uint8_t), 512, output);
        }
    }

}