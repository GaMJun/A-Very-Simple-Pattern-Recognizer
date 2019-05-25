//
// Created by gamjun on 14/05/19.
//

#include <iostream>
#include "pattern_occurrences_finder.h"
#include "../Structs/structs.h"

void findPixelsBelongingToLeaf(Matriz &pixel_map, int i, int j, pattern *padrao) {
    Pixel blank_pixel{};
    blank_pixel.b = 0xFF;
    blank_pixel.g = 0xFF;
    blank_pixel.r = 0xFF;

    if ((pixel_map[i][j].b == (unsigned char) 0xFF && pixel_map[i][j].g == (unsigned char) 0xFF &&
         pixel_map[i][j].r == (unsigned char) 0xFF)) {
        return;
    } else {
        pixel_position temp_pixel(i, j);

        padrao->pixels.push_back(temp_pixel);

        pixel_map[i][j] = blank_pixel;

        findPixelsBelongingToLeaf(pixel_map, i - 1, j - 1, padrao);
        findPixelsBelongingToLeaf(pixel_map, i - 1, j, padrao);
        findPixelsBelongingToLeaf(pixel_map, i - 1, j + 1, padrao);
        findPixelsBelongingToLeaf(pixel_map, i, j - 1, padrao);
        findPixelsBelongingToLeaf(pixel_map, i, j + 1, padrao);
        findPixelsBelongingToLeaf(pixel_map, i + 1, j - 1, padrao);
        findPixelsBelongingToLeaf(pixel_map, i + 1, j, padrao);
        findPixelsBelongingToLeaf(pixel_map, i + 1, j + 1, padrao);
    }
}

void PatternOccurrencesFinder::POF(Matriz &pixel_map, BMPInfoHeader *bmp_info_header) {
    vector<pattern> patterns{};

    for (int i = 1; i < bmp_info_header->height - 1; i++) {
        for (int j = 1; j < bmp_info_header->width - 1; j++) {
            if ((pixel_map[i][j].b == (unsigned char) 0x00 && pixel_map[i][j].g == (unsigned char) 0x00 &&
                 pixel_map[i][j].r == (unsigned char) 0x00)) {

                pattern padrao{};

                findPixelsBelongingToLeaf(pixel_map, i, j, &padrao);
                if (padrao.pixels.size() > 1000) {
                    patterns.push_back(padrao);
                }
            }
        }
    }

    for (auto &pattern : patterns) {
        if (pattern.pixels.size() >= 32619 && pattern.pixels.size() <= 33446) {
            for (auto &index : pattern.pixels) {
                pixel_map[index.linha][index.coluna].b = 0x00;
                pixel_map[index.linha][index.coluna].g = 0x00;
                pixel_map[index.linha][index.coluna].r = 0xFF;
            }
        } else if (pattern.pixels.size() >= 34408 && pattern.pixels.size() <= 34924) {
            for (auto &index : pattern.pixels) {
                pixel_map[index.linha][index.coluna].b = 0x00;
                pixel_map[index.linha][index.coluna].g = 0xFF;
                pixel_map[index.linha][index.coluna].r = 0x00;
            }
        } else if (pattern.pixels.size() >= 34925 && pattern.pixels.size() <= 36954) {
            for (auto &index : pattern.pixels) {
                pixel_map[index.linha][index.coluna].b = 0xFF;
                pixel_map[index.linha][index.coluna].g = 0x00;
                pixel_map[index.linha][index.coluna].r = 0x00;
            }
        } else if (pattern.pixels.size() >= 49327 && pattern.pixels.size() <= 50265) {
            for (auto &index : pattern.pixels) {
                pixel_map[index.linha][index.coluna].b = 0xFF;
                pixel_map[index.linha][index.coluna].g = 0x00;
                pixel_map[index.linha][index.coluna].r = 0xFF;
            }
        } else if (pattern.pixels.size() >= 75049 && pattern.pixels.size() <= 78103) {
            for (auto &index : pattern.pixels) {
                pixel_map[index.linha][index.coluna].b = 0x00;
                pixel_map[index.linha][index.coluna].g = 0xFF;
                pixel_map[index.linha][index.coluna].r = 0xFF;
            }
        } else if (pattern.pixels.size() >= 78852 && pattern.pixels.size() <= 79720) {
            for (auto &index : pattern.pixels) {
                pixel_map[index.linha][index.coluna].b = 0xFF;
                pixel_map[index.linha][index.coluna].g = 0xFF;
                pixel_map[index.linha][index.coluna].r = 0x00;
            }
        } else {
            for (auto &index : pattern.pixels) {
                pixel_map[index.linha][index.coluna].b = 0x00;
                pixel_map[index.linha][index.coluna].g = 0x00;
                pixel_map[index.linha][index.coluna].r = 0x00;
            }
        }

    }
}
