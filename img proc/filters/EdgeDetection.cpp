#include "EdgeDetection.h"

void EdgeDetection::Use(Image &image, std::vector<std::string> params) {
    float threshold = 0;

    try {
        threshold = std::stof(params[0]);
    } catch (const std::exception &) {
        throw std::runtime_error("Threshold is not float!!");
    }

    Grayscale gs;
    gs.Use(image, {});
    Image newimg(image.Width(), image.Height());

    for (int i = 0; i < image.Width(); ++i) {
        for (int j = 0; j < image.Height(); ++j) {
            float pix = (-1.0f) * image.GetRgb(i, j + 1).r_ + (-1.0f) * image.GetRgb(i - 1, j).r_ +
                        (-1.0f) * image.GetRgb(i + 1, j).r_ + (-1.0f) * image.GetRgb(i, j - 1).r_ +
                        4.0f * image.GetRgb(i, j).r_;  // NOLINT
            if (pix > threshold) {
                pix = 1;
            } else {
                pix = 0;
            }
            newimg.ChangePixel(RGB(pix, pix, pix), i, j);
        }
    }
    image = newimg;
}
