#include "Blur.h"
#include <cmath>
#include <numbers>
#include <iostream>

void BlurDir(Image &image, float sgm, bool dir) {
    Image newimg(image.Width(), image.Height());
    float prec1 = 1 / (sgm * std::sqrt(2 * std::numbers::pi));  // NOLINT
    float prec2 = expf(-1 / (2 * powf(sgm, 2)));                // NOLINT
    for (int x = 0; x < image.Width(); ++x) {
        for (int y = 0; y < image.Height(); ++y) {
            float r = 0;
            float g = 0;
            float b = 0;
            for (int z = static_cast<int>(-3 * sgm); z < static_cast<int>(3 * sgm); ++z) {
                float eq = prec1 * powf(prec2, static_cast<float>(pow(z, 2)));
                RGB pix;
                if (dir) {
                    pix = image.GetRgb(x + z, y);
                } else {
                    pix = image.GetRgb(x, y + z);
                }
                r += eq * pix.r_;
                g += eq * pix.g_;
                b += eq * pix.b_;
            }
            newimg.ChangePixel(RGB(r, g, b), x, y);
        }
    }
    image = newimg;
}

void Blur::Use(Image &image, std::vector<std::string> params) {
    float sgm = 0;
    try {
        sgm = std::stof(params[0]);
    } catch (const std::exception &) {
        throw std::runtime_error("Sigma is not float!!!");
    }
    BlurDir(image, sgm, true);
    BlurDir(image, sgm, false);
}
