//
// Created by gamjun on 01/05/19.
//

#ifndef PID_STRUCTS_H
#define PID_STRUCTS_H

#include <vector>

using namespace std;

//14 bytes
struct BMPFileHeader {
    unsigned short int file_type;  // File type always BM which is 0x4D42
    unsigned int file_size;        // Size of the file (in bytes)
    unsigned short int reserved1;  // Reserved, always 0
    unsigned short int reserved2;  // Reserved, always 0
    unsigned int offset_data;      // Start position of pixel_position data (bytes from the beginning of the file)
}__attribute__((packed));

//40 bytes
struct BMPInfoHeader {
    unsigned int size;             // Size of this header (in bytes)
    int width;                     // Width of bitmap in pixels
    int height;                    // height of bitmap in pixels
    unsigned short int planes;     // No. of planes for the target device, this is always 1
    unsigned short int bit_count;  // No. of bits per pixel_position
    unsigned int compression;      // 0 or 3 - uncompressed. THIS PROGRAM CONSIDERS ONLY UNCOMPRESSED BMP images
    unsigned int size_image;       // Size of bit map
    int x_pixels_per_meter;        //
    int y_pixels_per_meter;        //
    unsigned int colors_used;      // No. color indexes in the color table. Use 0 for the max number of colors allowed by bit_count
    unsigned int colors_important; // No. of colors used for displaying the bitmap. If 0 all colors are required
}__attribute__((packed));

//3 bytes
struct Pixel {
    unsigned char b = (unsigned char) 0x00;
    unsigned char g = (unsigned char) 0x00;
    unsigned char r = (unsigned char) 0x00;
}__attribute__((packed));

typedef vector<std::vector<Pixel>> Matriz;

class pixel_position {
public:
    int linha;
    int coluna;
    pixel_position(int linha, int coluna) : linha(linha), coluna(coluna) {}
};

class pattern {
public:
    pattern() {}
    vector<pixel_position> pixels;
};

#endif //PID_STRUCTS_H
