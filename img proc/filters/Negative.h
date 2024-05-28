#pragma once

#include "../Filter.h"

class Negative : public Filter {
public:
    Negative(){};
    ~Negative() override{};
    void Use(Image& image, std::vector<std::string> params) override;
};
