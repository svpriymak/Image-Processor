#include "BMP.h"

void BMP::Save(const char* path, Image& image) {
    std::ofstream file;
    file.open(path, std::ios::out | std::ios::binary);

    if (!file.is_open()) {
        throw std::runtime_error("File can't be saved");
    }

    unsigned char paddings[3];
    const unsigned char count_paddings = (4 - (image.Width() * 3) % 4) % 4;  // NOLINT

    const int file_size = BMP::FILE_HEADER_SIZE + BMP::INFO_HEADER_SIZE + image.Height() * image.Width() * 3 +
                          count_paddings * image.Height();

    unsigned char file_header[BMP::FILE_HEADER_SIZE];
    unsigned char info_header[BMP::INFO_HEADER_SIZE];

    BMP::CreateFileHeader(file_header, file_size);
    BMP::CreateInfoHeader(info_header, image.Width(), image.Height());

    file.write(reinterpret_cast<char*>(file_header), BMP::FILE_HEADER_SIZE);
    file.write(reinterpret_cast<char*>(info_header), BMP::INFO_HEADER_SIZE);

    RGB pixel;
    for (int y = 0; y < image.Height(); ++y) {
        for (int x = 0; x < image.Width(); ++x) {
            pixel = image.GetRgb(x, y);

            unsigned char color[3] = {static_cast<unsigned char>(pixel.b_ * 255.0f),   // NOLINT
                                      static_cast<unsigned char>(pixel.g_ * 255.0f),   // NOLINT
                                      static_cast<unsigned char>(pixel.r_ * 255.0f)};  // NOLINT
            file.write(reinterpret_cast<char*>(color), 3);
        }

        file.write(reinterpret_cast<char*>(paddings), count_paddings);
    }

    file.close();
}

Image BMP::Read(const char* path) {
    std::ifstream file;
    file.open(path, std::ios::in | std::ios::binary);

    if (!file.is_open()) {
        throw std::runtime_error("File can't be read");
    }

    unsigned char file_header[BMP::FILE_HEADER_SIZE];
    unsigned char info_header[BMP::INFO_HEADER_SIZE];

    file.read(reinterpret_cast<char*>(file_header), BMP::FILE_HEADER_SIZE);
    file.read(reinterpret_cast<char*>(info_header), BMP::INFO_HEADER_SIZE);

    if (file_header[0] != 'B' || file_header[1] != 'M') {
        throw std::runtime_error("Not a BMP file");
    }

    int width = (info_header[4]) + (info_header[5] << 8) + (info_header[6] << 16) + (info_header[7] << 24);  // NOLINT
    int height =
        (info_header[8]) + (info_header[9] << 8) + (info_header[10] << 16) + (info_header[11] << 24);  // NOLINT
    std::vector<std::vector<RGB>> pixels;

    pixels.resize(height);

    for (std::vector<RGB>& row : pixels) {
        row.resize(width);
    }

    const unsigned char count_paddings = (4 - (width * 3) % 4) % 4;  // NOLINT

    for (int y = 0; y < height; ++y) {
        for (int x = 0; x < width; ++x) {
            unsigned char pixel[3];
            file.read(reinterpret_cast<char*>(pixel), 3);
            pixels[y][x] = RGB(static_cast<float>(pixel[2]) / 255.0f,   // NOLINT
                               static_cast<float>(pixel[1]) / 255.0f,   // NOLINT
                               static_cast<float>(pixel[0]) / 255.0f);  // NOLINT
        }

        file.ignore(count_paddings);
    }

    file.close();

    return Image(width, height, pixels);
}

void BMP::CreateFileHeader(unsigned char* file_header, const int file_size) {
    file_header[0] = 'B';
    file_header[1] = 'M';
    file_header[2] = file_size;
    file_header[3] = file_size >> 8;   // NOLINT
    file_header[4] = file_size >> 16;  // NOLINT
    file_header[5] = file_size >> 24;  // NOLINT

    for (int i = 6; i < BMP::FILE_HEADER_SIZE; ++i) {  // NOLINT
        if (i == 10) {                                 // NOLINT
            file_header[i] = BMP::FILE_HEADER_SIZE + BMP::INFO_HEADER_SIZE;
            continue;
        }

        file_header[i] = 0;
    }
}

void BMP::CreateInfoHeader(unsigned char* info_header, const int width, const int height) {
    info_header[0] = BMP::INFO_HEADER_SIZE;
    info_header[1] = 0;
    info_header[2] = 0;
    info_header[3] = 0;

    info_header[4] = width;
    info_header[5] = width >> 8;   // NOLINT
    info_header[6] = width >> 16;  // NOLINT
    info_header[7] = width >> 24;  // NOLINT

    info_header[8] = height;         // NOLINT
    info_header[9] = height >> 8;    // NOLINT
    info_header[10] = height >> 16;  // NOLINT
    info_header[11] = height >> 24;  // NOLINT

    info_header[12] = 1;   // NOLINT
    info_header[13] = 0;   // NOLINT
    info_header[14] = 24;  // NOLINT

    for (int i = 15; i < BMP::INFO_HEADER_SIZE; ++i) {  // NOLINT
        info_header[i] = 0;
    }

    info_header[24] = 35;  // NOLINT
    info_header[25] = 46;  // NOLINT
    info_header[28] = 35;  // NOLINT
    info_header[29] = 46;  // NOLINT
}
