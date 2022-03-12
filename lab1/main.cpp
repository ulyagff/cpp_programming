#include <iostream>
#include <vector>
#include <cstdarg>
#include <cmath>
#include "Dot.h"


class Polyline {

public:

    Polyline() {
        count_unit = 0;
    }

    Polyline(int num, ...) {
        int x = 0, y = 0;
        Dot a;
        va_list args;
        va_start(args, num);
        if (num == 0) count_unit = 0;
        else {
            count_unit = num - 1;
            while (num--) {
                x = va_arg(args, int);
                y = va_arg(args, int);
                a.x = x;
                a.y = y;
                coordinate.push_back(a);
            }
        }
        va_end(args);
    }

    Polyline(const Polyline &poly) {
        count_unit = poly.count_unit;
        coordinate = poly.coordinate;
    }

    Polyline & operator = (const Polyline &poly) {
        count_unit = poly.count_unit;
        coordinate = poly.coordinate;
        return *this;
    }

    virtual float perimeter() const {
        float per = 0;
        int unit = 0;
        for (int i = 0; i < count_unit; i++) {
            unit = sqrt(pow((coordinate[i].x - coordinate[i + 1].x), 2) + pow((coordinate[i].y - coordinate[i + 1].y), 2));
            per += unit;
        }
        return per;
    }

protected:
    int count_unit;
    std::vector <Dot> coordinate;

};

class Closed_polyline: public Polyline {

public:

    Closed_polyline() : Polyline() {}

    Closed_polyline(int num, ...) {
        int x = 0, y = 0;
        Dot a;
        va_list args;
        va_start(args, num);
        count_unit = num;
        while (num--) {
            x = va_arg(args, int);
            y = va_arg(args, int);
            a.x = x; a.y = y;
            coordinate.push_back(a);
        }
        va_end(args);
    }

    Closed_polyline(const Closed_polyline &c_poly) {
        count_unit = c_poly.count_unit;
        coordinate = c_poly.coordinate;
    }

    Closed_polyline & operator = (const Closed_polyline &c_poly) {
        count_unit = c_poly.count_unit;
        coordinate = c_poly.coordinate;
        return *this;
    }

    float perimeter() const override{
        int unit = 0;
        float per = 0;
        for (int i = 0; i < count_unit - 1; i++) {
            unit = sqrt(pow((coordinate[i].x - coordinate[i + 1].x), 2) + pow((coordinate[i].y - coordinate[i + 1].y), 2));
            per += unit;
        }
        unit = sqrt(pow((coordinate[0].x - coordinate[count_unit - 1].x), 2) + pow((coordinate[0].y - coordinate[count_unit - 1].y), 2));
        per+=unit;
        return per;
    }

};

class r_polygon {
public:
    r_polygon() {
        count_unit = 0;
    }

    r_polygon(std::vector<Dot> &d) {
        count_unit = d.size();
        coordinate = d;
    }

    r_polygon(const r_polygon &polyg) {
        count_unit = polyg.count_unit;
        coordinate = polyg.coordinate;
    }

    r_polygon & operator = (const r_polygon &polyg) {
        count_unit = polyg.count_unit;
        coordinate = polyg.coordinate;
        return *this;
    }

    float perimeter() const{
        float per = 0;
        int unit = 0;
        for (int i = 0; i < count_unit - 1; i++) {
            unit = sqrt(pow((coordinate[i].x - coordinate[i + 1].x), 2) + pow((coordinate[i].y - coordinate[i + 1].y), 2));
            per += unit;
        }
        unit = sqrt(pow((coordinate[0].x - coordinate[count_unit - 1].x), 2) + pow((coordinate[0].y - coordinate[count_unit - 1].y), 2));
        per+=unit;
        return per;
    }

    float area() const{
        float s = 0;
        for (int i = 0; i < count_unit; i++) {
            if (i == 0)
                s += coordinate[i].x * (coordinate[i + 1].y - coordinate[count_unit - 1].y);
            else if (i == count_unit - 1)
                s += coordinate[i].x * (coordinate[0].y - coordinate[i - 1].y);
            else s += coordinate[i].x * (coordinate[i + 1].y - coordinate[i - 1].y);
        }
        s /= 2;
        return abs(s);
    }

protected:
    int count_unit;
    std::vector <Dot> coordinate;
};

class Triangle : public r_polygon {
public:
    Triangle(std::vector<Dot> &d) {
            if (d.size() == 3) {
                count_unit = d.size();
                coordinate = d;
            }
            else std::cout << "this is not a triangle";
    }

    Triangle(const Triangle &tri) {
        for (int i = 0; i < 3; i++) coordinate[i] = tri.coordinate[i];
    }

    Triangle & operator = (const Triangle &tri) {
        for (int i = 0; i < 3; i++) coordinate[i] = tri.coordinate[i];
        return *this;
    }
};


class Trapeze : public r_polygon {
public:

    explicit Trapeze(std::vector<Dot> &d) {
            if (d.size() == 4) {
                count_unit = d.size();
                coordinate = d;
            }
            else std::cout << "this is not a trapeze";
    }


    Trapeze(const Trapeze &tra) {
        for (int i = 0; i < 4; i++) coordinate[i] = tra.coordinate[i];
    }

    Trapeze & operator = (const Trapeze &tri) {
        for (int i = 0; i < 4; i++) coordinate[i] = tri.coordinate[i];
        return *this;
    }

};

class right_polygon : public r_polygon{
public:
    right_polygon(std::vector<Dot> &d) {
        count_unit = d.size();
        coordinate = d;
    }

    right_polygon(const right_polygon &r_polyg) {
        count_unit = r_polyg.count_unit;
        coordinate = r_polyg.coordinate;
    }

    right_polygon & operator = (const right_polygon &r_polyg) {
        count_unit = r_polyg.count_unit;
        coordinate = r_polyg.coordinate;
        return *this;
    }

};

int main() {
    Dot a(1, 1), b(2, 4), c(3, 1);
    std::vector<Dot> l{a, b, c};
    Triangle ex(l);


    Polyline n;
    Polyline ex3(3, 1, 1, 3, 3, 5, 4);
    ex3.perimeter();
    Closed_polyline ex1;
    Closed_polyline ex2(3, 1, 1, 2, 4, 3, 1);
    Closed_polyline ex4(3, 1, 2, 2, 4, 3, 1);

    Polyline **ex5 = new Polyline*[3];
    ex5[0] = &ex3;
    ex5[1] = &ex2;
    ex5[2] = &ex4;
    std::cout << ex2.perimeter() << std::endl;

    for (int i = 0; i < 3; i++) {
        std::cout << ex5[i]->perimeter() << std::endl;
    }


    return 0;
}
