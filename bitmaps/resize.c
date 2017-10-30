/**
 * Scales a BMP by integer scale fator in range [1-100]
 * Usage: resize scale_factor infile outfile
 */

#include <stdio.h>
#include <stdlib.h>

#include "bmp.h"

int main(int argc, char *argv[])
{
    // ensure proper usage
    if (argc != 4)
    {
        fprintf(stderr, "Usage: ./resize scale_factor infile outfile\n");
        return 1;
    }

    // remember filenames and scale factor
    int scale_factor = atoi(argv[1]);
    char *infile = argv[2];
    char *outfile = argv[3];
    //check for valid scale factor
    if (scale_factor < 1 || scale_factor > 100)
    {
        fprintf(stderr, "Scale factor range [1,100]\n");
        return 1;

    }

    // open input file
    FILE *inptr = fopen(infile, "r");
    if (inptr == NULL)
    {
        fprintf(stderr, "Could not open %s.\n", infile);
        return 2;
    }

    // open output file
    FILE *outptr = fopen(outfile, "w");
    if (outptr == NULL)
    {
        fclose(inptr);
        fprintf(stderr, "Could not create %s.\n", outfile);
        return 3;
    }

    // read infile's BITMAPFILEHEADER
    BITMAPFILEHEADER bf;
    fread(&bf, sizeof(BITMAPFILEHEADER), 1, inptr);

    // read infile's BITMAPINFOHEADER
    BITMAPINFOHEADER bi;
    fread(&bi, sizeof(BITMAPINFOHEADER), 1, inptr);

    // ensure infile is (likely) a 24-bit uncompressed BMP 4.0
    if (bf.bfType != 0x4d42 || bf.bfOffBits != 54 || bi.biSize != 40 ||
        bi.biBitCount != 24 || bi.biCompression != 0)
    {
        fclose(outptr);
        fclose(inptr);
        fprintf(stderr, "Unsupported file format.\n");
        return 4;
    }
    // determine padding for scanlines
    int infile_padding = (4 - (bi.biWidth * sizeof(RGBTRIPLE)) % 4) % 4;

    //scale headers for output file
    long input_width = bi.biWidth;
    long input_height = bi.biHeight;
    bi.biWidth *= scale_factor;
    bi.biHeight *= scale_factor;
    // determine padding for scanlines
    int outfile_padding = (4 - (bi.biWidth * sizeof(RGBTRIPLE)) % 4) % 4;

    bi.biSizeImage = ((sizeof(RGBTRIPLE)*bi.biWidth) + outfile_padding)*abs(bi.biHeight);
    bf.bfSize = bi.biSizeImage + sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER);


    // write outfile's BITMAPFILEHEADER
    fwrite(&bf, sizeof(BITMAPFILEHEADER), 1, outptr);

    // write outfile's BITMAPINFOHEADER
    fwrite(&bi, sizeof(BITMAPINFOHEADER), 1, outptr);


    // iterate over infile's scanlines
    for (int i = 0, biHeight = labs(input_height); i < biHeight; i++)
    {
        for (int h = 0; h < scale_factor; h++)
        {
            // iterate over pixels in scanline
            for (int j = 0; j < input_width; j++)
            {
                // temporary storage
                RGBTRIPLE triple;

                // read RGB triple from infile
                fread(&triple, sizeof(RGBTRIPLE), 1, inptr);

                for (int k = 0; k < scale_factor; k++)
                {
                    // write RGB triple to outfile
                    fwrite(&triple, sizeof(RGBTRIPLE), 1, outptr);
                }
            }
            //  add padding
            for (int k = 0; k < outfile_padding; k++)
            {
                fputc(0x00, outptr);
            }
            //return to start of scan line to duplicate row
            fseek(inptr, (-1)*input_width*sizeof(RGBTRIPLE), SEEK_CUR);
        }

        // skip to beginning of next line
        fseek(inptr, infile_padding + input_width*sizeof(RGBTRIPLE), SEEK_CUR);


    }

    // close infile
    fclose(inptr);

    // close outfile
    fclose(outptr);

    // success
    return 0;
}
