//
// Created by ulyag on 04.03.2022.
//

#include "Dot.h"

Dot& Dot:: operator = (const Dot &dot) {
    x = dot.x;
    y = dot.y;

    return *this;
}
