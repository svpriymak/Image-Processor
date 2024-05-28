#pragma once

#include <vector>
#include <stack>
#include <map>
#include <iostream>
#include <stdexcept>

#include "Filter.h"
#include "filters/Negative.h"
#include "filters/Grayscale.h"
#include "filters/Crop.h"
#include "filters/Blur.h"
#include "filters/Sharpening.h"
#include "filters/EdgeDetection.h"
#include "filters/Custom.h"
#include "BMP.h"

class Parser {
private:
    int argc_;
    std::stack<char*> argv_;

    std::map<std::string, int> args_count_map_;
    std::map<std::string, Filter*> filters_map_;

public:
    Parser(int argc, char** argv);
    ~Parser();

    void Run();

    void ParseFilters(Image& image);

    void Help();
};
