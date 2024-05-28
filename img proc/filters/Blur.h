#pragma once

#include "../Filter.h"

class Blur : public Filter {
public:
    Blur(){};
    ~Blur() override{};
    void Use(Image& image, std::vector<std::string> params) override;
};
