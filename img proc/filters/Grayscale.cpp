#include "Grayscale.h"

void Grayscale::Use(Image& image, std::vector<std::string> params) {
    for (int x = 0; x < image.Width(); ++x) {
        for (int y = 0; y < image.Height(); ++y) {

            float r = image.GetRgb(x, y).r_ * 0.299 + image.GetRgb(x, y).g_ * 0.587 +  // NOLINT
                      image.GetRgb(x, y).b_ * 0.114;                                   // NOLINT
            float g = image.GetRgb(x, y).r_ * 0.299 + image.GetRgb(x, y).g_ * 0.587 +  // NOLINT
                      image.GetRgb(x, y).b_ * 0.114;                                   // NOLINT
            float b = image.GetRgb(x, y).r_ * 0.299 + image.GetRgb(x, y).g_ * 0.587 +  // NOLINT
                      image.GetRgb(x, y).b_ * 0.114;                                   // NOLINT

            image.ChangePixel(RGB(r, g, b), x, y);
        }
    }
}
