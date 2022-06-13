//
// Created by ulyag on 04.03.2022.
//

#include "Dot.h"

Dot& Dot:: operator = (const Dot &dot) {
    x = dot.x;
    y = dot.y;

    return *this;
}

bool Dot::operator!=(const Dot &dot) {
    if (x != dot.x)
        return false;
    if (y != dot.y)
        return false;
    return true;
}