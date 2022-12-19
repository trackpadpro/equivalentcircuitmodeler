#if !defined(CIRCUIT_H)
#define CIRCUIT_H

#include <numbers>
#include <complex>
#include <memory>
#include <vector>
#include <cmath>
#include <map>

class Impedance{
    public:
        virtual std::complex<double> simplify(const double& freq); //freq in rad/s
        std::map<double,std::complex<double>> sweep(const double& freqMin,const double& freqMax,const double& step = 0.1);
    protected:
        std::complex<double> Z;
};

class Circuit: public Impedance{
    public:
        Circuit(std::vector<std::vector<std::shared_ptr<Impedance>>> circuit);
        std::complex<double> simplify(const double& freq);
    private:
        std::vector<std::vector<std::shared_ptr<Impedance>>> components;
};

std::map<double,double> bode(std::map<double,std::complex<double>> sweep);  //freq in rad/s, mag in dB
std::map<double,double> nyquist(std::map<double,std::complex<double>> sweep);

class Resistor: public Impedance{
    public:
        Resistor(double ohm);
        std::complex<double> simplify(const double& freq);
    private:
        double R;
};

class Inductor: public Impedance{
    public:
        Inductor(double henry);
        std::complex<double> simplify(const double& freq);
    private:
        double L;
};

class Capacitor: public Impedance{
    public:
        Capacitor(double coulomb);
        std::complex<double> simplify(const double& freq);
    private:
        double C;
};

#endif
