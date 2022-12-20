#if !defined(CIRCUIT_H)
#define CIRCUIT_H

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
        Circuit(const std::vector<std::vector<std::shared_ptr<Impedance>>>& circuit);
        std::complex<double> simplify(const double& freq);
    private:
        std::vector<std::vector<std::shared_ptr<Impedance>>> components;
};

std::map<double,double> bode(const std::map<double,std::complex<double>>& sweep);  //freq in rad/s, mag in dB
std::map<double,double> nyquist(const std::map<double,std::complex<double>>& sweep);

class Resistor: public Impedance{
    public:
        Resistor(const double& ohm);
    private:
        double R;
};

class Inductor: public Impedance{
    public:
        Inductor(const double& henry);
        std::complex<double> simplify(const double& freq);
    private:
        double L;
};

class Capacitor: public Impedance{
    public:
        Capacitor(const double& coulomb);
        std::complex<double> simplify(const double& freq);
    private:
        double C;
};

class Warburg: public Impedance{
    public:
        Warburg(const double& A_W);
        std::complex<double> simplify(const double& freq);
    private:
        double A;
};

#endif
