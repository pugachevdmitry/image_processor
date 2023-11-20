#include <iostream>
#include <vector>
#include <stdexcept>

#include "Image.h"
#include "FilterController.h"

int main(int argc, char** argv) {
    try {
        if (argc == 1) {
            std::cout << "Program to apply filters on BMP images.\n"
                      << "Usage: {program name} {path to input file} {path to output file} [-{filter name 1}"
                      << " [first parameter] [second parameter] ...] [-{filter name 2} [first parameter]"
                      << "[second parameter] ...] ...\n";
            return 0;
        }
        if (argc < 3) {
            throw std::invalid_argument("Too few arguments!");
        }

        Image img(argv[1]);
        FilterController controller;

        size_t cur_arg = 3;
        while (cur_arg < argc) {
            if (argv[cur_arg][0] != '-') {
                throw std::invalid_argument("Bad argument");
            }
            std::string filter_name = argv[cur_arg];
            filter_name.erase(filter_name.begin());
            std::vector<std::string> arguments;
            while (cur_arg + 1 < argc && argv[cur_arg + 1][0] != '-') {
                ++cur_arg;
                arguments.push_back(argv[cur_arg]);
            }

            img = controller.ApplyFilter(img, filter_name, arguments);

            ++cur_arg;
        }

        img.WriteToFile(argv[2]);
    } catch (const std::exception& e) {
        std::cout << "A exception was caught with message '" << e.what() << "'\n";
    }
    return 0;
}
