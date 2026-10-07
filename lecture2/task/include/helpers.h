//
// Created by MohamedBakr on 10/7/2026.
//

#ifndef HELPERS_H
#define HELPERS_H

#include <iostream>
#include <string>

namespace helpers {


    template <typename Func>
    void printSection(const std::string& name, Func func) {
        std::cout << name << ": ";
        func();
    }

    void printSearchResult(int value, bool found);

    void printDivider();

} // namespace helpers

#endif // HELPERS_H
