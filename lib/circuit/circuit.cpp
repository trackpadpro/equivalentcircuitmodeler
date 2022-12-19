#include "circuit.h"

std::complex<double> Impedance::simplify(const double& freq){
    return Z;
}

std::complex<double> Circuit::simplify(const double& freq){
    std::complex<double> branch;
    Z = 0;

    for(auto& series: components){
        branch = 0;

        for(auto& parallel: series){
            branch+=1.0/parallel->simplify(freq);
        }

        Z+=1.0/branch;
    }

    return Z;
}

std::complex<double> Resistor::simplify(const double& freq){
    return Z;
}

std::complex<double> Inductor::simplify(const double& freq){
    Z = std::polar(freq*L,std::numbers::pi*0.5);

    return Z;
}

std::complex<double> Capacitor::simplify(const double& freq){
    Z = std::polar(1.0/(freq*C),-std::numbers::pi*0.5);

    return Z;
}

std::map<double,std::complex<double>> Impedance::sweep(const double& freqMin,const double& freqMax,const double& step){
    std::map<double,std::complex<double>> Zsweep;

    for(double freq = freqMin;freq<=freqMax;freq+=step){
        Zsweep.emplace(freq,simplify(freq));
    }

    return Zsweep;
}

std::map<double,double> bode(std::map<double,std::complex<double>> sweep){
    std::map<double,double> bod;

    for(const auto& [freq,Z]: sweep){
        bod.emplace(freq,20*log10(abs(Z)));
    }

    return bod;
}

std::map<double,double> nyquist(std::map<double,std::complex<double>> sweep){
    std::map<double,double> nyq;

    for(const auto& [freq,Z]: sweep){
        nyq.emplace(real(Z),imag(Z));
    }

    return nyq;
}

Circuit::Circuit(std::vector<std::vector<std::shared_ptr<Impedance>>> circuit){
    components = circuit;
}

Resistor::Resistor(double ohm){
    R = ohm;
    Z = ohm;
}

Inductor::Inductor(double henry){
    L = henry;
}

Capacitor::Capacitor(double coulomb){
    C = coulomb;
}
