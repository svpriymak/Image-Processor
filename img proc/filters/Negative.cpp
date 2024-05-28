#include "Negative.h"

void Negative::Use(Image& image, std::vector<std::string> params) {
    for (int x = 0; x < image.Width(); ++x) {
        for (int y = 0; y < image.Height(); ++y) {
            float r = 1 - image.GetRgb(x, y).r_;
            float g = 1 - image.GetRgb(x, y).g_;
            float b = 1 - image.GetRgb(x, y).b_;

            image.ChangePixel(RGB(r, g, b), x, y);
        }
    }
}
