#pragma once

#include "../Filter.h"

class Custom : public Filter {
public:
    Custom(){};
    ~Custom() override{};
    void Use(Image& image, std::vector<std::string> params) override;
};
