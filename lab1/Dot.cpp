#include "Dot.h"

Dot& Dot:: operator = (const Dot &dot) {
    x = dot.x;
    y = dot.y;

    return *this;
}
