#include <iostream>
#include <map>
#include <vector>
#include <string>

class Polynom {
public:
    Polynom() {}
    Polynom(std::vector<std::pair<int, int>> c) {
        for (int i = 0; i < c.size(); i++) {
            cof.emplace(c[i]);
        }
    }

    ~Polynom() {}

    Polynom(const Polynom &pol) {
        cof = pol.cof;
    }

    Polynom & operator =(const Polynom &pol) {
        cof = pol.cof;
        return *this;
    }

    bool operator==(const Polynom &pol) {
        return cof == pol.cof;
    }

    bool operator!=(const Polynom &pol) {
        return !(cof == pol.cof);
    }

    Polynom operator+() const {
        return *this;
    }

    Polynom operator-() {
        auto it = cof.begin();
        while (it != cof.end()) {
            it->second = -it->second;
            it++;
        }

        return *this;
    }

    friend std::istream& operator>> (std::istream &in, Polynom &p) {
        std::string s, koef = "", deg = "";
        int flag_k = 0;
        getline(in, s);
        for (int i = 0; i < s.size(); i++) {
            if (flag_k == 0 && s[i] > 47 && s[i] < 58 )
                koef+=s[i];

            if (s[i] == 'x') {
                flag_k = 1;
                if (koef == "") koef = "1";
            }

            if (flag_k == 1 && s[i] > 47 && s[i] < 58 ) {
                deg += s[i];
            }

            if (s[i] == ' ' || i == (s.size() - 1)) {
                if (deg == "" && flag_k == 0) deg = "0";
                else if (deg == "" && flag_k == 1) deg = "1";
                p.cof.insert(std::make_pair(std::stoi(deg), std::stoi(koef)));
                koef = "";
                deg = "";
                flag_k = 0;
            }
        }
        return in;
    }

    friend std::ostream& operator<< (std::ostream &out, Polynom &p) {
        auto it = p.cof.begin();
        while (it != p.cof.end()) {
            if (it->second != 0) {
                if (it->first == 0)
                    out << it->second << ' ';
                else if (it->first == 1) {
                    if (it->second == 1)
                        out << "x ";
                    else
                        out << it->second << "x ";

                }
                else
                if (it->second == 1)
                    out << "x^" << it->first << ' ';
                else
                    out << it->second << "x^" << it->first << ' ';
            }
            it++;
        }
        return out;
    }

    Polynom operator+( Polynom &p) {
        Polynom c_l = *this;
        auto it_l = c_l.cof.begin();

        auto it_r = p.cof.begin();
        while (it_r != p.cof.end()) {
            it_l = c_l.cof.find(it_r->first);
            if (it_l != c_l.cof.end()) it_l->second+=it_r->second;
            else c_l.cof.insert(std::make_pair(it_r->first, it_r->second));
            it_r++;
        }
        return c_l;
    }

    Polynom operator-( Polynom &p) {
        Polynom c_l = *this;
        auto it_l = c_l.cof.begin();
        -p;

        auto it_r = p.cof.begin();
        while (it_r != p.cof.end()) {
            it_l = c_l.cof.find(it_r->first);
            if (it_l != c_l.cof.end()) it_l->second+=it_r->second;
            else c_l.cof.insert(std::make_pair(it_r->first, it_r->second));
            it_r++;
        }
        -p;
        return c_l;
    }

    Polynom operator+=( Polynom &p) {
        auto it_l = cof.begin();

        auto it_r = p.cof.begin();
        while (it_r != p.cof.end()) {
            it_l = cof.find(it_r->first);
            if (it_l != cof.end()) it_l->second+=it_r->second;
            else cof.insert(std::make_pair(it_r->first, it_r->second));
            it_r++;
        }
        return *this;
    }

    Polynom operator-=( Polynom &p) {
        auto it_l = cof.begin();
        -p;
        auto it_r = p.cof.begin();
        while (it_r != p.cof.end()) {
            it_l = cof.find(it_r->first);
            if (it_l != cof.end()) it_l->second+=it_r->second;
            else cof.insert(std::make_pair(it_r->first, it_r->second));
            it_r++;
        }
        -p;
        return *this;
    }

    Polynom operator*( int &n) {
        Polynom c_l = *this;
        auto it_l = c_l.cof.begin();

        while (it_l != c_l.cof.end()) {
            it_l->second *= n;
            it_l++;
        }
        return c_l;
    }

    Polynom operator*=( int &n) {
        auto it_l = cof.begin();

        while (it_l != cof.end()) {
            it_l->second *= n;
            it_l++;
        }
        return *this;
    }

    Polynom operator*( Polynom &p) {
        Polynom res;
        auto it_res = res.cof.begin();

        Polynom c_l = *this;
        auto it_l = c_l.cof.begin();

        auto it_r = p.cof.begin();
        int cur_deg, cur_cof;
        while (it_r != p.cof.end()) {
            while (it_l != c_l.cof.end()) {
                cur_deg = it_r->first + it_l->first;
                cur_cof = it_r->second * it_l->second;
                it_res = res.cof.find(cur_deg);
                if (it_res != res.cof.end()) it_res->second+=cur_cof;
                else res.cof.insert(std::make_pair(cur_deg, cur_cof));
                it_l++;
            }
            it_r++;
            it_l = c_l.cof.begin();

        }
        return res;
    }

    Polynom operator*=( Polynom &p) {
        Polynom res;
        auto it_res = res.cof.begin();

        Polynom c_l = *this;
        auto it_l = c_l.cof.begin();

        auto it_r = p.cof.begin();
        int cur_deg, cur_cof;
        while (it_r != p.cof.end()) {
            while (it_l != c_l.cof.end()) {
                cur_deg = it_r->first + it_l->first;
                cur_cof = it_r->second * it_l->second;
                it_res = res.cof.find(cur_deg);
                if (it_res != res.cof.end()) it_res->second+=cur_cof;
                else res.cof.insert(std::make_pair(cur_deg, cur_cof));
                it_l++;
            }
            it_r++;
            it_l = c_l.cof.begin();

        }
        *this = res;
        return *this;
    }

    int& operator[](int n) {
        auto it = cof.begin();
        it = cof.find(n);
        if (it != cof.end())
            return it->second;
        else {
            cof.insert(std::make_pair(n , 0));
            return cof.find(n)->second;
        }
    }

    Polynom integral() {
        auto it = cof.begin();
        Polynom res;
        int cur_deg, cur_cof;
        while (it != cof.end()) {
            if (it->second != 0) {
                cur_deg = it->first + 1;
                cur_cof = (it->second)/(cur_deg);
                res.cof.insert(std::make_pair(cur_deg, cur_cof));
            }
            it++;
        }
        return res;
    }

    Polynom derivative() {
        auto it = cof.begin();
        Polynom res;
        int cur_deg, cur_cof;
        while (it != cof.end()) {
            if (it->second != 0) {
                if (it->first != 0) {
                    cur_deg = it->first - 1;
                    cur_cof = (it->second) * (cur_deg);
                    res.cof.insert(std::make_pair(cur_deg, cur_cof));
                }
            }
            it++;
        }
        return res;
    }
private:
    std::map<int, int> cof;
};

int main() {
//    std::map<int, int> cof;
//    cof[0] = 5;
//    cof[1] = 3;
//    cof[6] = 9;
//    std::map<int, int> cof2;
//    cof2 = cof;
//    cof[7] = 7;
//    bool y = cof2 == cof;
    std::vector<std::pair<int, int>> p;
    p.emplace_back(2, 1);
    p.emplace_back(1, 2);
    p.emplace_back(0, 1);

    std::vector<std::pair<int, int>> q;
    q.emplace_back(3, 1);
    q.emplace_back(1, 4);

    q.emplace_back(0, 2);

    Polynom ex1(p);
    Polynom ex2 (q);

    Polynom ex3;
    std::cin >> ex3;

    std::cout << ex1 << '\n' << ex2 << std::endl;
    return 0;
}