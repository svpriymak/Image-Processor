#include "Custom.h"

void Custom::Use(Image &image, std::vector<std::string> params) {
    float sgm = std::stof(params[0]);
    for (int x = 0; x < image.Width(); ++x) {
        for (int y = 0; y < image.Height(); ++y) {

            float r = image.GetRgb(x, y).r_ * sgm + image.GetRgb(x, y).g_ + image.GetRgb(x, y).b_;  // NOLINT
            float g = image.GetRgb(x, y).r_ + image.GetRgb(x, y).g_ * sgm + image.GetRgb(x, y).b_;  // NOLINT
            float b = image.GetRgb(x, y).r_ + image.GetRgb(x, y).g_ + image.GetRgb(x, y).b_ * sgm;  // NOLINT

            image.ChangePixel(RGB(r, g, b), x, y);
        }
    }
}
