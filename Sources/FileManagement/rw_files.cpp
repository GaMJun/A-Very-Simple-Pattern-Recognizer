//
// Created by gamjun on 01/05/19.
//
#include <fstream>
#include <algorithm>
#include <iostream>
#include <cstring>
#include <vector>
#include "rw_files.h"

#include "../Structs/structs.h"

Matriz Rw_files::read_file(const string &file_path, BMPFileHeader *file_header, BMPInfoHeader *bmp_info_header) {

    ifstream in_file(file_path, ifstream::binary | ios::in);

    if (!in_file) {
        cout << "Erro ao ler o arquivo. Certifique-se que o arquivo existe!" << endl;
        exit(1);
    }

    in_file.read((char *) file_header, sizeof(BMPFileHeader));

    if (file_header->file_type != 0x4D42) {
        cout << "Erro: Arquivo não suportado! Deve necessariamente ser do formato BMP." << endl;
        exit(2);
    }

    in_file.read((char *) bmp_info_header, sizeof(BMPInfoHeader));

    if ((bmp_info_header->compression != 0x00 && bmp_info_header->compression != 0x03) ||
        bmp_info_header->bit_count != 0x18) {

        cout << "Erro: Arquivo não suportado! O arquivo BMP não deve ser comprimido." << endl;
        exit(3);
    }


    Matriz pixel_map(bmp_info_header->height, vector<Pixel>(bmp_info_header->width));

    Pixel temp_pixel{};

    for (int i = 0; i < bmp_info_header->height; i++) {
        for (int j = 0; j < bmp_info_header->width; j++) {
            in_file.read(reinterpret_cast<char *>(&temp_pixel), sizeof(temp_pixel));
            pixel_map[i][j] = temp_pixel;
        }

        in_file.seekg((bmp_info_header->bit_count / 8) *
                      (4 - (bmp_info_header->width % 4 == 0 ? 4 : bmp_info_header->width % 4)) +
                      in_file.tellg());

        if (in_file.tellg() != (bmp_info_header->bit_count / 8) *
                               (4 - (bmp_info_header->width % 4 == 0 ? 4 : bmp_info_header->width % 4)) +
                               in_file.tellg()) {
        }
    }
    in_file.close();

    return pixel_map;

}

void Rw_files::write_results(string archive_name, BMPFileHeader file_header, BMPInfoHeader bmp_info_header,
                             Matriz pixel_map) {
    ofstream result_file;

    result_file.open("../Results/" + archive_name, ofstream::binary | ios::out);
    result_file.write((char *) &file_header, sizeof(BMPFileHeader));
    result_file.write((char *) &bmp_info_header, sizeof(BMPInfoHeader));

    Pixel temp_pixel{}, padding{};

    for (int i = 0; i < bmp_info_header.height; i++) {
        for (int j = 0; j < bmp_info_header.width; j++) {
            temp_pixel = pixel_map[i][j];
            result_file.write((char *) &temp_pixel, sizeof(Pixel));
        }
        for (int padSz = 0; padSz < (4 - (bmp_info_header.width % 4 == 0 ? 4 : bmp_info_header.width % 4)); padSz++) {
            result_file.write((char *) &padding, sizeof(Pixel));
        }

    }
    result_file.close();
}