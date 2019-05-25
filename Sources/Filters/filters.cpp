//
// Created by gamjun on 01/05/19.
//

#include <iostream>
#include <cstring>
#include "filters.h"

void Filters::ShadesOfBlack(Matriz &pixel_map, BMPInfoHeader *bmp_info_header) {

    for (int i = 0; i < bmp_info_header->height; i++) {
        for (int j = 0; j < bmp_info_header->width; j++) {
            pixel_map[i][j].b = ((pixel_map[i][j].b + pixel_map[i][j].g + pixel_map[i][j].r) / 3) < (unsigned char) 0xEB
                                ? (unsigned char) 0x00 : (unsigned char) 0xFF;
            pixel_map[i][j].g = ((pixel_map[i][j].b + pixel_map[i][j].g + pixel_map[i][j].r) / 3) < (unsigned char) 0xEB
                                ? (unsigned char) 0x00 : (unsigned char) 0xFF;
            pixel_map[i][j].r = ((pixel_map[i][j].b + pixel_map[i][j].g + pixel_map[i][j].r) / 3) < (unsigned char) 0xEB
                                ? (unsigned char) 0x00 : (unsigned char) 0xFF;
        }
    }
}

void Filters::HighFrequencyFilter(Matriz &pixel_map, BMPInfoHeader *bmp_info_header) {
    int B = 0, G = 0, R = 0;

    int filter[3][3] = {{-1, -1, -1},
                        {-1, 8,  -1},
                        {-1, -1, -1}};

    Matriz pixel_map_border = pixel_map;

    Pixel black_pixel{};

    for (int i = 1; i < bmp_info_header->height - 1; i++) {
        for (int j = 1; j < bmp_info_header->width - 1; j++) {
            B = (pixel_map[i - 1][j - 1].b * filter[0][0] +
                 pixel_map[i - 1][j].b * filter[0][1] +
                 pixel_map[i - 1][j + 1].b * filter[0][2] +

                 pixel_map[i][j - 1].b * filter[1][0] +
                 pixel_map[i][j].b * filter[1][1] +
                 pixel_map[i][j + 1].b * filter[1][2] +

                 pixel_map[i + 1][j - 1].b * filter[2][0] +
                 pixel_map[i + 1][j].b * filter[2][1] +
                 pixel_map[i + 1][j + 1].b * filter[2][2]);

            G = pixel_map[i - 1][j - 1].g * filter[0][0] +
                pixel_map[i - 1][j].g * filter[0][1] +
                pixel_map[i - 1][j + 1].g * filter[0][2] +

                pixel_map[i][j - 1].g * filter[1][0] +
                pixel_map[i][j].g * filter[1][1] +
                pixel_map[i][j + 1].g * filter[1][2] +

                pixel_map[i + 1][j - 1].g * filter[2][0] +
                pixel_map[i + 1][j].g * filter[2][1] +
                pixel_map[i + 1][j + 1].g * filter[2][2];

            R = pixel_map[i - 1][j - 1].r * filter[0][0] +
                pixel_map[i - 1][j].r * filter[0][1] +
                pixel_map[i - 1][j + 1].r * filter[0][2] +

                pixel_map[i][j - 1].r * filter[1][0] +
                pixel_map[i][j].r * filter[1][1] +
                pixel_map[i][j + 1].r * filter[1][2] +

                pixel_map[i + 1][j - 1].r * filter[2][0] +
                pixel_map[i + 1][j].r * filter[2][1] +
                pixel_map[i + 1][j + 1].r * filter[2][2];

            if (B > 0xFF) {
                pixel_map_border[i][j].b = (unsigned char) 0xFF;
            } else if (B < 0x00) {
                pixel_map_border[i][j].b = (unsigned char) 0x00;
            } else {
                pixel_map_border[i][j].b = (unsigned char) B;
            }

            if (G > 0xFF) {
                pixel_map_border[i][j].g = (unsigned char) 0xFF;
            } else if (G < 0x00) {
                pixel_map_border[i][j].g = (unsigned char) 0x00;
            } else {
                pixel_map_border[i][j].g = (unsigned char) G;
            }

            if (R > 0xFF) {
                pixel_map_border[i][j].r = (unsigned char) 0xFF;
            } else if (R < 0x00) {
                pixel_map_border[i][j].r = (unsigned char) 0x00;
            } else {
                pixel_map_border[i][j].r = (unsigned char) R;
            }
        }
    }

    for (int i = 0; i < bmp_info_header->width; i++) {
        pixel_map_border[0][i] = black_pixel;
    }

    for (int i = 0; i < bmp_info_header->width; i++) {
        pixel_map_border[bmp_info_header->height - 1][i] = black_pixel;
    }

    for (int i = 0; i < bmp_info_header->height; i++) {
        pixel_map_border[i][0] = black_pixel;
    }

    for (int i = 0; i < bmp_info_header->height; i++) {
        pixel_map_border[i][bmp_info_header->width - 1] = black_pixel;
    }

    pixel_map = pixel_map_border;
}