#include "Sharpening.h"

void Sharpening::Use(Image &image, std::vector<std::string> params) {
    int x = image.Width();
    int y = image.Height();
    Image newimg(x, y);

    for (int i = 0; i < x; ++i) {
        for (int j = 0; j < y; ++j) {
            float pix_r = (-1) * image.GetRgb(i, j + 1).r_ + (-1) * image.GetRgb(i - 1, j).r_ +
                          (-1) * image.GetRgb(i + 1, j).r_ + (-1) * image.GetRgb(i, j - 1).r_ +
                          5 * image.GetRgb(i, j).r_;  // NOLINT
            float pix_g = (-1) * image.GetRgb(i, j + 1).g_ + (-1) * image.GetRgb(i - 1, j).g_ +
                          (-1) * image.GetRgb(i + 1, j).g_ + (-1) * image.GetRgb(i, j - 1).g_ +
                          5 * image.GetRgb(i, j).g_;  // NOLINT
            float pix_b = (-1) * image.GetRgb(i, j + 1).b_ + (-1) * image.GetRgb(i - 1, j).b_ +
                          (-1) * image.GetRgb(i + 1, j).b_ + (-1) * image.GetRgb(i, j - 1).b_ +
                          5 * image.GetRgb(i, j).b_;  // NOLINT

            pix_r = std::max(std::min(pix_r, 1.0f), 0.0f);
            pix_g = std::max(std::min(pix_g, 1.0f), 0.0f);
            pix_b = std::max(std::min(pix_b, 1.0f), 0.0f);

            newimg.ChangePixel(RGB(pix_r, pix_g, pix_b), i, j);
        }
    }
    image = newimg;
}
