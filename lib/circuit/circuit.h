#if !defined(CIRCUIT_H)
#define CIRCUIT_H

#include <fstream>
#include <vector>
#include <cmath>

class Impedance{
    public:
        bool simplify(double freq); //freq in rad/s
    protected:
        double real, imag, R, L, C, mag, phase;
};

class Circuit: public Impedance{
    public:
        friend std::fstream& operator>>(std::fstream& os,Circuit& input);
        friend std::fstream& operator<<(std::fstream& os,const Circuit& output);
    private:
        std::vector<std::vector<Impedance*>> components;
};

#endif
