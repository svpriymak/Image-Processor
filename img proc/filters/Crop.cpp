#include "Crop.h"

void Crop::Use(Image &image, std::vector<std::string> params) {
    int width = 0;
    int height = 0;

    try {
        width = std::stoi(params[0]);
        height = std::stoi(params[1]);
    } catch (const std::exception &) {
        throw std::runtime_error("Width or height is not int!!");
    }

    Image cropped(std::min(width, image.Width()), std::min(height, image.Height()));
    for (int x = 0; x < cropped.Width(); ++x) {
        for (int y = image.Height() - cropped.Height(); y < image.Height(); ++y) {
            cropped.ChangePixel(image.GetRgb(x, y), x, y - (image.Height() - cropped.Height()));
        }
    }
    image = cropped;
}
