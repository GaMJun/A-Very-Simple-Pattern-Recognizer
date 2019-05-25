//
// Created by gamjun on 01/05/19.
//

#include <iostream>
#include <fstream>
#include <vector>
#include <math.h>
#include <unistd.h>
#include <ctime>
#include <iomanip>

#include "Sources/FileManagement/rw_files.h"
#include "Sources/Structs/structs.h"
#include "Sources/Filters/filters.h"
#include "Sources/PatternOccurrencesFinder/pattern_occurrences_finder.h"

using namespace std;

double timespecToSec(struct timespec *time) {
    return (double) (time->tv_sec * 1000000000 + time->tv_nsec) / 1000000000.0;
}

int main(int argc, char const *argv[]) {

    float allTimeCPU = 0;

    cout << fixed;
    cout << setprecision(5);

    for (int i = 1; i <= 10; i++) {
        cout << endl << "Fazendo o processo de identificação do arquivo /Entries/" << i << ".bmp" << endl;

        BMPFileHeader file_header{};
        BMPInfoHeader bmp_info_header{};
        Matriz pixel_map{}, border_pixel_map{};
        struct timespec startCPU{}, endCPU{};
        float allArchiveCPU = 0;

        cout << "Lendo arquivo /Entries/" + to_string(i) + ".bmp\t\t\t\t\t\t=> ";
        sync();
        clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &startCPU);

        pixel_map = Rw_files::read_file("../Entries/" + to_string(i) + ".bmp", &file_header, &bmp_info_header);

        clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &endCPU);
        allArchiveCPU = allArchiveCPU + timespecToSec(&endCPU) - timespecToSec(&startCPU);
        cout << timespecToSec(&endCPU) - timespecToSec(&startCPU) << "\tseg" << endl;

        cout << "Escrevendo arquivo /Entries/" + to_string(i) + "|1-Original.bmp\t\t=> ";
        sync();
        clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &startCPU);

        Rw_files::write_results(to_string(i) + "|1-Original.bmp", file_header, bmp_info_header, pixel_map);

        clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &endCPU);
        allArchiveCPU = allArchiveCPU + timespecToSec(&endCPU) - timespecToSec(&startCPU);
        cout << timespecToSec(&endCPU) - timespecToSec(&startCPU) << "\tseg" << endl;

        cout << "Aplicando Limiarização\t\t\t\t\t\t\t\t=> ";
        sync();
        clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &startCPU);

        Filters::ShadesOfBlack(pixel_map, &bmp_info_header);

        clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &endCPU);
        allArchiveCPU = allArchiveCPU + timespecToSec(&endCPU) - timespecToSec(&startCPU);
        cout << timespecToSec(&endCPU) - timespecToSec(&startCPU) << "\tseg" << endl;

        cout << "Escrevendo arquivo /Entries/" + to_string(i) + "|2-BlackAndWhite.bmp\t=> ";
        sync();
        clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &startCPU);

        Rw_files::write_results(to_string(i) + "|2-BlackAndWhite.bmp", file_header, bmp_info_header, pixel_map);

        clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &endCPU);
        allArchiveCPU = allArchiveCPU + timespecToSec(&endCPU) - timespecToSec(&startCPU);
        cout << timespecToSec(&endCPU) - timespecToSec(&startCPU) << "\tseg" << endl;

        cout << "Aplicando Filtro Passa-Alta\t\t\t\t\t\t\t=> ";
        sync();
        clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &startCPU);

        border_pixel_map = pixel_map;

        Filters::HighFrequencyFilter(border_pixel_map, &bmp_info_header);

        clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &endCPU);
        allArchiveCPU = allArchiveCPU + timespecToSec(&endCPU) - timespecToSec(&startCPU);
        cout << timespecToSec(&endCPU) - timespecToSec(&startCPU) << "\tseg" << endl;

        cout << "Escrevendo arquivo /Entries/" + to_string(i) + "|3-Borders.bmp \t\t=> ";
        sync();
        clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &startCPU);

        Rw_files::write_results(to_string(i) + "|3-Borders.bmp", file_header, bmp_info_header, border_pixel_map);

        clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &endCPU);
        allArchiveCPU = allArchiveCPU + timespecToSec(&endCPU) - timespecToSec(&startCPU);
        cout << timespecToSec(&endCPU) - timespecToSec(&startCPU) << "\tseg" << endl;

        cout << "Encontrando e identificando padrões\t\t\t\t\t=> ";
        sync();
        clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &startCPU);

        PatternOccurrencesFinder::POF(pixel_map, &bmp_info_header);

        clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &endCPU);
        allArchiveCPU = allArchiveCPU + timespecToSec(&endCPU) - timespecToSec(&startCPU);
        cout << timespecToSec(&endCPU) - timespecToSec(&startCPU) << "\tseg" << endl;

        cout << "Escrevendo arquivo /Entries/" + to_string(i) + "|4-FinalPatterns.bmp\t=> ";
        sync();
        clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &startCPU);

        Rw_files::write_results(to_string(i) + "|4-FinalPatterns.bmp", file_header, bmp_info_header, pixel_map);

        clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &endCPU);
        allArchiveCPU = allArchiveCPU + timespecToSec(&endCPU) - timespecToSec(&startCPU);
        cout << timespecToSec(&endCPU) - timespecToSec(&startCPU) << "\tseg" << endl;

        allTimeCPU = allTimeCPU + allArchiveCPU;
    }
    cout << endl << "Tempo total de execução\t\t\t\t\t\t\t\t=> " << allTimeCPU << "\tseg" << endl;

    exit(0);
}