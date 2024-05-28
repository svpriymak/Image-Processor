#pragma once

#include "../Filter.h"

class Grayscale : public Filter {
public:
    Grayscale(){};
    ~Grayscale() override{};
    void Use(Image& image, std::vector<std::string> params) override;
};
