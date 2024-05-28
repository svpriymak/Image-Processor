#pragma once

#include "../Filter.h"

class Crop : public Filter {
public:
    Crop(){};
    ~Crop() override{};
    void Use(Image& image, std::vector<std::string> params) override;
};
