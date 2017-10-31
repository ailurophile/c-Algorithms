/* Program to recover pictures from camera memory card with FAT file system*/
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdbool.h>

#define BLOCKSIZE  512

int main(int argc, char* argv[])
{
    // ensure proper usage
    if (argc != 2)
    {
        fprintf(stderr, "Usage: ./recover image\n");
        return 1;
    }
        // open input file
    FILE *inptr = fopen(argv[1], "r");
    if (inptr == NULL)
    {
        fprintf(stderr, "Could not open %s.\n", argv[1]);
        return 2;
    }
    char filename[8]; //to hold JPG filenames of form ###.jpg
    bool found = false; //not yet processing an image
    unsigned char block[BLOCKSIZE]; //to hold 1 block of data from memory card
    FILE *image = NULL; //pointer to current image being recovered
    int count = 0;
    while(fread(block, 1, BLOCKSIZE, inptr) == BLOCKSIZE)
    {
         if((block[0] == 0xff) && (block[1] == 0xd8) && (block[2] == 0xff) && ((block[3] & 0xe0) == 0xe0))
        {
            if (!found)  //this is the first image located
            {
                found = true;
              }
            else
            {
                fclose(image);
            }
            int size = snprintf(filename,sizeof(filename), "%03i.jpg", count++);
            if (size >= sizeof(filename))
            {
                fprintf(stderr, "Overflowed filename\n");
                return 4;
            }
            image = fopen(filename, "w");
            if (image == NULL)
            {
                fprintf(stderr, "Could not open %03i.jpg.\n", count);
                return 3;
            }

        }
        if (found)
        {
            fwrite(block, BLOCKSIZE, 1, image);
        }

    }
    fclose(inptr);
    if (image != NULL)
    {
        fclose(image);
    }
    return 0;

}
