#pragma once

#include "Image.h"

#include <fstream>
#include <cstdint>

class BMP {
public:
    static const char FILE_HEADER_SIZE = 14;
    static const char INFO_HEADER_SIZE = 40;

public:
    static void CreateFileHeader(unsigned char* file_header, const int file_size);

    static void CreateInfoHeader(unsigned char* info_header, const int width, const int height);

    static void Save(const char* path, Image& image);

    static Image Read(const char* path);
};