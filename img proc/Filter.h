#pragma once

#include "Image.h"

#include <vector>
#include <string>
#include <stdexcept>

class Filter {
public:
    Filter(){};
    virtual ~Filter(){};
    virtual void Use(Image& image, std::vector<std::string> params);
};
