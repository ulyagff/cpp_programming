

#ifndef CLASSES_DOT_H
#define CLASSES_DOT_H


class Dot {
public:
    int x;
    int y;

    explicit Dot(int x = 0, int y = 0) : x(x), y(y) {}

    Dot(const Dot &dot) : x(dot.x), y(dot.y) {}

    ~Dot() {}

    Dot & operator = (const Dot &dot);
    bool operator!=(const Dot &dot);
};


#endif //CLASSES_DOT_H
