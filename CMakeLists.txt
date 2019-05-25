cmake_minimum_required(VERSION 3.14)
project(PID)

set(CMAKE_CXX_STANDARD 17)

add_executable(PID main.cpp Sources/FileManagement/rw_files.cpp Sources/FileManagement/rw_files.h Sources/Structs/structs.h Sources/Filters/filters.cpp Sources/Filters/filters.h Sources/PatternOccurrencesFinder/pattern_occurrences_finder.cpp Sources/PatternOccurrencesFinder/pattern_occurrences_finder.h)