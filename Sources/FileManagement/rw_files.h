//
// Created by gamjun on 01/05/19.
//

#ifndef PID_RW_FILES_H
#define PID_RW_FILES_H

#include "../Structs/structs.h"

using namespace std;

class Rw_files {
public:
    static Matriz read_file(const string &file_path, BMPFileHeader *file_header, BMPInfoHeader *bmp_info_header);

    static void write_results(string archive_name, BMPFileHeader file_header, BMPInfoHeader bmp_info_header, Matriz pixel_map);

};


#endif //PID_RW_FILES_H
