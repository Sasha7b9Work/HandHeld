/****************************************************************************
	Парсер из pbm в символы 1602 дисплея
	Михаил Белкин <dltech174@gmail.com> 2023

*****************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <inttypes.h>
#include "out.h"

int main()
{
    uint8_t shift[4] = {0,5,80,85};
    FILE *img;

    if ((img = fopen("img1602.h", "w")) == NULL) {
        return 0;
    }

    // for(uint8_t j=0 ; j<4 ; ++j) {
    //     fprintf(img, "seg%02d[8]\t= { ", 0+j*8);
    //     for(uint8_t i=0 ; i<7 ; ++i) {
    //         fprintf(img, "0x%02x, ", (MagickImage[shift[j]+10*i]>>3)&0x1f);
    //     }
    //     fprintf(img, "0x%02x };\n", (MagickImage[shift[j]+70]>>3)&0x1f);
    //
    //     fprintf(img, "seg%02d[8]\t= { ", 1+j*8);
    //     for(uint8_t i=0 ; i<7 ; ++i) {
    //         fprintf(img, "0x%02x, ", ((MagickImage[shift[j]+10*i]<<2) + (MagickImage[shift[j]+10*i+1]>>6))&0x1f);
    //     }
    //     fprintf(img, "0x%02x };\n", ((MagickImage[shift[j]+70]<<2) + (MagickImage[shift[j]+71]>>6))&0x1f);
    //
    //     fprintf(img, "seg%02d[8]\t= { ", 2+j*8);
    //     for(uint8_t i=0 ; i<7 ; ++i) {
    //         fprintf(img, "0x%02x, ", (MagickImage[shift[j]+10*i+1]>>1)&0x1f);
    //     }
    //     fprintf(img, "0x%02x };\n", (MagickImage[shift[j]+71]>>1)&0x1f);
    //
    //     fprintf(img, "seg%02d[8]\t= { ", 3+j*8);
    //     for(uint8_t i=0 ; i<7 ; ++i) {
    //         fprintf(img, "0x%02x, ", ((MagickImage[shift[j]+10*i+1]<<4) + (MagickImage[shift[j]+10*i+2]>>4))&0x1f);
    //     }
    //     fprintf(img, "0x%02x };\n", ((MagickImage[shift[j]+71]<<4) + (MagickImage[shift[j]+72]>>4))&0x1f);
    //
    //     fprintf(img, "seg%02d[8]\t= { ", 4+j*8);
    //     for(uint8_t i=0 ; i<7 ; ++i) {
    //         fprintf(img, "0x%02x, ", (MagickImage[shift[j]+10*i+2]<<1 + MagickImage[shift[j]+10*i+3]>>7)&0x1f);
    //     }
    //     fprintf(img, "0x%02x };\n", (MagickImage[shift[j]+72]<<1 + MagickImage[shift[j]+73]>>7)&0x1f);
    //
    //     fprintf(img, "seg%02d[8]\t= { ", 5+j*8);
    //     for(uint8_t i=0 ; i<7 ; ++i) {
    //         fprintf(img, "0x%02x, ", (MagickImage[shift[j]+10*i+3]>>2)&0x1f);
    //     }
    //     fprintf(img, "0x%02x };\n", (MagickImage[shift[j]+73]>>2)&0x1f);
    //
    //     fprintf(img, "seg%02d[8]\t= { ", 6+j*8);
    //     for(uint8_t i=0 ; i<7 ; ++i) {
    //         fprintf(img, "0x%02x, ", (MagickImage[shift[j]+10*i+3]<<3 + MagickImage[shift[j]+10*i+4]>>5)&0x1f);
    //     }
    //     fprintf(img, "0x%02x };\n", (MagickImage[shift[j]+73]<<3 + MagickImage[shift[j]+74]>>5)&0x1f);
    //
    //     fprintf(img, "seg%02d[8]\t= { ", 7+j*8);
    //     for(uint8_t i=0 ; i<7 ; ++i) {
    //         fprintf(img, "0x%02x, ", (MagickImage[shift[j]+10*i+4])&0x1f);
    //     }
    //     fprintf(img, "0x%02x };\n\n", (MagickImage[shift[j]+74])&0x1f);
    // }

    fprintf(img, "const uint8_t segs[32][8] = { ");
    for(uint8_t j=0 ; j<4 ; ++j) {
        if( j==0 )  fprintf(img, "{ ");
        else        fprintf(img, "\t\t\t\t\t\t\t{ ");
        for(uint8_t i=0 ; i<7 ; ++i) {
            fprintf(img, "0x%02x, ", (MagickImage[shift[j]+10*i]>>3)&0x1f);
        }
        fprintf(img, "0x%02x },\n", (MagickImage[shift[j]+70]>>3)&0x1f);

        fprintf(img, "\t\t\t\t\t\t\t{ ");
        for(uint8_t i=0 ; i<7 ; ++i) {
            fprintf(img, "0x%02x, ", ((MagickImage[shift[j]+10*i]<<2) + (MagickImage[shift[j]+10*i+1]>>6))&0x1f);
        }
        fprintf(img, "0x%02x },\n", ((MagickImage[shift[j]+70]<<2) + (MagickImage[shift[j]+71]>>6))&0x1f);

        fprintf(img, "\t\t\t\t\t\t\t{ ");
        for(uint8_t i=0 ; i<7 ; ++i) {
            fprintf(img, "0x%02x, ", (MagickImage[shift[j]+10*i+1]>>1)&0x1f);
        }
        fprintf(img, "0x%02x },\n", (MagickImage[shift[j]+71]>>1)&0x1f);

        fprintf(img, "\t\t\t\t\t\t\t{ ");
        for(uint8_t i=0 ; i<7 ; ++i) {
            fprintf(img, "0x%02x, ", ((MagickImage[shift[j]+10*i+1]<<4) + (MagickImage[shift[j]+10*i+2]>>4))&0x1f);
        }
        fprintf(img, "0x%02x },\n", ((MagickImage[shift[j]+71]<<4) + (MagickImage[shift[j]+72]>>4))&0x1f);

        fprintf(img, "\t\t\t\t\t\t\t{ ");
        for(uint8_t i=0 ; i<7 ; ++i) {
            fprintf(img, "0x%02x, ", ((MagickImage[shift[j]+10*i+2]<<1) + (MagickImage[shift[j]+10*i+3]>>7))&0x1f);
        }
        fprintf(img, "0x%02x },\n", ((MagickImage[shift[j]+72]<<1) + (MagickImage[shift[j]+73]>>7))&0x1f);

        fprintf(img, "\t\t\t\t\t\t\t{ ");
        for(uint8_t i=0 ; i<7 ; ++i) {
            fprintf(img, "0x%02x, ", (MagickImage[shift[j]+10*i+3]>>2)&0x1f);
        }
        fprintf(img, "0x%02x },\n", (MagickImage[shift[j]+73]>>2)&0x1f);

        fprintf(img, "\t\t\t\t\t\t\t{ ");
        for(uint8_t i=0 ; i<7 ; ++i) {
            fprintf(img, "0x%02x, ", ((MagickImage[shift[j]+10*i+3]<<3) + (MagickImage[shift[j]+10*i+4]>>5))&0x1f);
        }
        fprintf(img, "0x%02x },\n", ((MagickImage[shift[j]+73]<<3) + (MagickImage[shift[j]+74]>>5))&0x1f);

        fprintf(img, "\t\t\t\t\t\t\t{ ");
        for(uint8_t i=0 ; i<7 ; ++i) {
            fprintf(img, "0x%02x, ", (MagickImage[shift[j]+10*i+4])&0x1f);
        }
        if( j==3 )  fprintf(img, "0x%02x } };", (MagickImage[shift[j]+74])&0x1f);
        else        fprintf(img, "0x%02x },\n\n", (MagickImage[shift[j]+74])&0x1f);
    }

    fclose(img);
    return 0;
}
