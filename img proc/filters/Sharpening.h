#pragma once

#include "../Filter.h"

class Sharpening : public Filter {
public:
    Sharpening(){};
    ~Sharpening() override{};
    void Use(Image& image, std::vector<std::string> params) override;
};
