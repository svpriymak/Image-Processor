#include "Parser.h"

Parser::Parser(int argc, char** argv) {
    argc_ = argc;

    for (int i = argc - 1; i > 0; --i) {
        argv_.push(argv[i]);
    }

    filters_map_["-neg"] = new Negative();
    filters_map_["-gs"] = new Grayscale();
    filters_map_["-crop"] = new Crop();
    filters_map_["-blur"] = new Blur();
    filters_map_["-sharp"] = new Sharpening();
    filters_map_["-edge"] = new EdgeDetection();
    filters_map_["-custom"] = new Custom();

    args_count_map_["-neg"] = 0;
    args_count_map_["-gs"] = 0;
    args_count_map_["-crop"] = 2;
    args_count_map_["-blur"] = 1;
    args_count_map_["-sharp"] = 0;
    args_count_map_["-edge"] = 1;
    args_count_map_["-custom"] = 1;
}

void Parser::Help() {
    std::cout << "-neg converts your image to negative. It does not require any args." << std::endl;
    std::cout << "-gs converts your image to grayscale. It does not require any args." << std::endl;
    std::cout << "-crop cuts your image to the given size. It requires 2 args: width and height. (starting point is "
                 "the left upper corner)"
              << std::endl;
    std::cout << "-sharp makes your image sharper. It does not require any args." << std::endl;
    std::cout << "-edge makes your image grayscaled and applies certain matrix to every pixel (look it up in read.me). "
                 "It requires 1 arg: threshold from 0 to 1."
              << std::endl;
    std::cout << "-blur makes your image blurred. It requires 1 arg: blur value (works properly if value is > 0, seems "
                 "to be unlimited in upper border)."
              << std::endl;
    std::cout << "-custom changes your picture in a way I prefer. It requires 1 arg: value from 0 (I call this effect "
                 "hallucinogenic mushrooms. This filter requires more testing. The best result I discovered was on "
                 "values from 8 to 15) :)."
              << std::endl;
}

void Parser::Run() {
    if (argc_ == 1) {
        Help();
        return;
    }

    if (argc_ == 2) {
        throw std::runtime_error("No out file");
    }

    Image image = BMP::Read(argv_.top());
    argv_.pop();

    char* output_file = argv_.top();
    argv_.pop();

    if (!argv_.empty()) {
        ParseFilters(image);
    }

    BMP::Save(output_file, image);
}

void Parser::ParseFilters(Image& image) {
    char* filter_tag = argv_.top();
    argv_.pop();

    if (args_count_map_.find(filter_tag) == args_count_map_.end()) {
        throw std::runtime_error("Not enough args");
    }

    std::vector<std::string> params;

    for (int i = 0; i < args_count_map_.find(filter_tag)->second; ++i) {
        params.push_back(argv_.top());
        argv_.pop();
    }

    filters_map_.find(filter_tag)->second->Use(image, params);

    if (!argv_.empty()) {
        ParseFilters(image);
    }
}
Parser::~Parser() {
    for (auto& filter : filters_map_) {
        delete filter.second;
    }
}
