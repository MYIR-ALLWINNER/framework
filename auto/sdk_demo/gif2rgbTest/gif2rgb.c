/*
 * @Description: Decode gif as rgb
 * @Version: 1.0
 * @Author: tangjianxiong
 * @Date: 2021-07-08 10:52:03
 * @LastEditors: tangjianxiong
 * @LastEditTime: 2021-08-03 10:56:40
 * @FilePath: \sdk_demo\gif2rgbTest\gif2rgb.c
 * Copyright (C) 2021 ALLWINNER. All rights reserved.
 */
#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdbool.h>
#include <fcntl.h>
#include "gif_lib.h"
#include "getarg.h"

#define PROGRAM_NAME	"gif2rgb"

#define MODULE_VERSION "V2.0.20220506"

/******************************************************************************
 The real screen dumping routine.
******************************************************************************/
static void DumpScreen2RGB(char *FileName,
                           ColorMapObject *ColorMap,
                           GifRowType *ScreenBuffer,
                           int ScreenWidth, int ScreenHeight)
{
    int i, j;
    GifRowType GifRow;
    GifColorType *ColorMapEntry;
    FILE *rgbfp[3];

    if (FileName != NULL) {
        if ((rgbfp[0] = fopen(FileName, "a+")) == NULL)
        GIF_EXIT("Can't open input file name.");
    } else {

        rgbfp[0] = stdout;
    }

    if (ColorMap == NULL) {
        fprintf(stderr, "Color map pointer is NULL.\n");
        exit(EXIT_FAILURE);
    }

    unsigned char *Buffer, *BufferP;

    if ((Buffer = (unsigned char *) malloc(ScreenWidth * 3)) == NULL)
    GIF_EXIT("Failed to allocate memory required, aborted.");
    for(int k = 0; k < 1; k++) {
        for (i = 0; i < ScreenHeight; i++) {
            GifRow = ScreenBuffer[i];
            printf("\b\b\b\b%-4d", ScreenHeight - i);
            for (j = 0, BufferP = Buffer; j < ScreenWidth; j++) {
                ColorMapEntry = &ColorMap->Colors[GifRow[j]];
                *BufferP++ = ColorMapEntry->Red;
                *BufferP++ = ColorMapEntry->Green;
                *BufferP++ = ColorMapEntry->Blue;
            }
            if (fwrite(Buffer, ScreenWidth * 3, 1, rgbfp[0]) != 1)
            GIF_EXIT("Write to file(s) failed.");
        }
    }

    free((char *) Buffer);
    fclose(rgbfp[0]);

}

static void GIF2RGB( char *FileName, char *OutFileNamePattern)
{
    int	i, j, Size, Row, Col, Width, Height, ExtCode, Count;
    GifRecordType RecordType;
    GifByteType *Extension;
    GifRowType *ScreenBuffer;
    GifFileType *GifFile;
    int
            InterlacedOffset[] = { 0, 4, 2, 1 }, /* The way Interlaced image should. */
    InterlacedJumps[] = { 8, 8, 4, 2 };    /* be read - offsets and jumps... */
    int ImageNum = 0;
    ColorMapObject *ColorMap;
    int Error;

    if ((GifFile = DGifOpenFileName(FileName, &Error)) == NULL) {
        printf("open gif file error.");
        exit(EXIT_FAILURE);
    }

    if (GifFile->SHeight == 0 || GifFile->SWidth == 0) {
        fprintf(stderr, "Image of width or height 0\n");
        exit(EXIT_FAILURE);
    }

    /*
     * Allocate the screen as vector of column of rows. Note this
     * screen is device independent - it's the screen defined by the
     * GIF file parameters.
     */
    if ((ScreenBuffer = (GifRowType *)
            malloc(GifFile->SHeight * sizeof(GifRowType))) == NULL)
    GIF_EXIT("Failed to allocate memory required, aborted.");

    Size = GifFile->SWidth * sizeof(GifPixelType);/* Size in bytes one row.*/
    if ((ScreenBuffer[0] = (GifRowType) malloc(Size)) == NULL) /* First row. */
    GIF_EXIT("Failed to allocate memory required, aborted.");

    for (i = 0; i < GifFile->SWidth; i++)  /* Set its color to BackGround. */
        ScreenBuffer[0][i] = GifFile->SBackGroundColor;
    for (i = 1; i < GifFile->SHeight; i++) {
        /* Allocate the other rows, and set their color to background too: */
        if ((ScreenBuffer[i] = (GifRowType) malloc(Size)) == NULL)
        GIF_EXIT("Failed to allocate memory required, aborted.");

        memcpy(ScreenBuffer[i], ScreenBuffer[0], Size);
    }

    int screenIndex = 0;
	char *name = (char*)malloc(255*sizeof(char));
    /* Scan the content of the GIF file and load the image(s) in: */
    do {
        if (DGifGetRecordType(GifFile, &RecordType) == GIF_ERROR) {
            printf("DGifGetRecordType error.");
            exit(EXIT_FAILURE);
        }
        switch (RecordType) {
            case IMAGE_DESC_RECORD_TYPE:
                if (DGifGetImageDesc(GifFile) == GIF_ERROR) {
                    printf("DGifGetImageDesc error.");
                    exit(EXIT_FAILURE);
                }
                Row = GifFile->Image.Top; /* Image Position relative to Screen. */
                Col = GifFile->Image.Left;
                Width = GifFile->Image.Width;
                Height = GifFile->Image.Height;
                printf("\n%s: Image %d at (%d, %d) [%dx%d]:     ",
                           PROGRAM_NAME, ++ImageNum, Col, Row, Width, Height);
                if (GifFile->Image.Left + GifFile->Image.Width > GifFile->SWidth ||
                    GifFile->Image.Top + GifFile->Image.Height > GifFile->SHeight) {
                    fprintf(stderr, "Image %d is not confined to screen dimension, aborted.\n",ImageNum);
                    exit(EXIT_FAILURE);
                }
                if (GifFile->Image.Interlace) {
                    /* Need to perform 4 passes on the images: */
                    for (Count = i = 0; i < 4; i++)
                        for (j = Row + InterlacedOffset[i]; j < Row + Height;
                             j += InterlacedJumps[i]) {
                            printf("\b\b\b\b%-4d", Count++);
                            if (DGifGetLine(GifFile, &ScreenBuffer[j][Col],
                                            Width) == GIF_ERROR) {
								printf("DGifGetLine error.");
                                exit(EXIT_FAILURE);
                            }
                        }
                }
                else {
                    for (i = 0; i < Height; i++) {
                        printf("\b\b\b\b%-4d", i);
                        if (DGifGetLine(GifFile, &ScreenBuffer[Row++][Col],
                                        Width) == GIF_ERROR) {
                            printf("DGifGetLine error.");
                            exit(EXIT_FAILURE);
                        }
                    }
                }

                /* Lets dump it - set the global variables required and do it: */
                ColorMap = (GifFile->Image.ColorMap
                            ? GifFile->Image.ColorMap
                            : GifFile->SColorMap);
                if (ColorMap == NULL) {
                    fprintf(stderr, "Gif Image does not have a colormap\n");
                    exit(EXIT_FAILURE);
                }

                /* check that the background color isn't garbage (SF bug #87) */
                if (GifFile->SBackGroundColor < 0 || GifFile->SBackGroundColor >= ColorMap->ColorCount) {
                    fprintf(stderr, "Background color out of range for colormap\n");
                    exit(EXIT_FAILURE);
                }

                sprintf(name, OutFileNamePattern, screenIndex++);
				printf("Final File Name: %s\n", name);

                DumpScreen2RGB(name,
                               ColorMap,
                               ScreenBuffer,
                               GifFile->SWidth, GifFile->SHeight);
                break;
            case EXTENSION_RECORD_TYPE:
                /* Skip any extension blocks in file: */
                if (DGifGetExtension(GifFile, &ExtCode, &Extension) == GIF_ERROR) {
                    printf("DGifGetExtension error.");
                    exit(EXIT_FAILURE);
                }
                while (Extension != NULL) {
                    if (DGifGetExtensionNext(GifFile, &Extension) == GIF_ERROR) {
                        printf("DGifGetExtensionNext error.");
                        exit(EXIT_FAILURE);
                    }
                }
                break;
            case TERMINATE_RECORD_TYPE:
                break;
            default:		    /* Should be trapped by DGifGetRecordType. */
                break;
        }
    } while (RecordType != TERMINATE_RECORD_TYPE);

    (void)free(ScreenBuffer);

    if (DGifCloseFile(GifFile, &Error) == GIF_ERROR) {
        printf("DGifCloseFile error.");
        exit(EXIT_FAILURE);
    }
    (void) free(name);
}

int main(int argc, char **argv) {
    printf("gif2rgb test version:%s\n", MODULE_VERSION);
    GIF2RGB("/tmp/rainbow.gif", "/tmp/rainbow-%d.rgb");
    return 0;
}