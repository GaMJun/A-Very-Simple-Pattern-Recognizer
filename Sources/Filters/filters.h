//
// Created by gamjun on 01/05/19.
//

#ifndef PID_FILTERS_H
#define PID_FILTERS_H

#include "../Structs/structs.h"

class Filters {
public:
    static void HighFrequencyFilter(Matriz &pixel_map, BMPInfoHeader *bmp_info_header);
    static void ShadesOfBlack(Matriz &pixel_map, BMPInfoHeader *bmp_info_header);


};


#endif //PID_FILTERS_H
