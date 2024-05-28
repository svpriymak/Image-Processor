#pragma once

#include "../Filter.h"

#include "Grayscale.h"

class EdgeDetection : public Filter {
public:
    EdgeDetection(){};
    ~EdgeDetection() override{};
    void Use(Image& image, std::vector<std::string> params) override;
};
