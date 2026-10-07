//
// Created by MohamedBakr on 10/7/2026.
//
#include "helpers.h"

namespace helpers {

    void printSearchResult(int value, bool found) {
        std::cout << "Search " << value << ": "
                  << (found ? "Found" : "Not Found")
                  << std::endl;
    }

    void printDivider() {
        std::cout << "-------------------==========-------------" << std::endl;
    }

} // namespace helpers