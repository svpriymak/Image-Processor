#include "Image.h"
#include <vector>

Image::Image() : width_(0), height_(0) {
}

Image::Image(int width, int height) : width_(width), height_(height), pixels_(height_, std::vector(width_, RGB())) {
}

Image::Image(int width, int height, std::vector<std::vector<RGB>> pixels)
    : width_(width), height_(height), pixels_(pixels) {
}

int Image::Width() const {
    return width_;
}

int Image::Height() const {
    return height_;
}

int Image::GetXPixels() const {
    return x_pixels_per_m_;
}
int Image::GetYPixels() const {
    return y_pixels_per_m_;
}

RGB Image::GetRgb(int x, int y) const {
    y = std::min(height_ - 1, std::max(y, 0));
    x = std::min(width_ - 1, std::max(x, 0));
    return pixels_[y][x];
}

void Image::ChangePixel(RGB rgb, int x, int y) {
    if (x < 0 || y < 0 || x > width_ - 1 || y > height_ - 1) {
        return;
    }
    pixels_[y][x] = rgb;
}

void Image::CopyFrom(Image& image) {
    for (int x = 0; x < width_; ++x) {
        for (int y = 0; y < height_; ++y) {
            Image::ChangePixel(image.GetRgb(x, y), x, y);
        }
    }
}

Image& Image::operator=(Image& new_image) {
    height_ = new_image.Height();
    width_ = new_image.Width();
    CopyFrom(new_image);

    return *this;
}
