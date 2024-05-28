#pragma once
#include "RGB.h"
#include <vector>

class Image {
private:
    int width_;
    int height_;
    int x_pixels_per_m_;
    int y_pixels_per_m_;
    std::vector<std::vector<RGB>> pixels_;

public:
    Image();
    Image(int width, int height);
    Image(int width, int height, std::vector<std::vector<RGB>> pixels);

    RGB GetRgb(int x, int y) const;
    void ChangePixel(RGB rgb, int x, int y);
    void CopyFrom(Image& image);

    int Width() const;
    int Height() const;
    int GetXPixels() const;
    int GetYPixels() const;

    Image& operator=(Image& new_image);
};
