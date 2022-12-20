#include <iomanip>
#include <fstream>

#include "circuit.h"

int main(){
    std::shared_ptr<Resistor> R_S = std::make_shared<Resistor>(5);
    std::shared_ptr<Resistor> R_CT = std::make_shared<Resistor>(5);
    std::shared_ptr<Capacitor> C = std::make_shared<Capacitor>(0.0005);

    Circuit A({{R_CT},{std::make_shared<Warburg>(2)}});
    Circuit B({{R_S},{std::make_shared<Circuit>(A),C}});

    {
        std::ofstream outCSV("./data/nyquist.csv");

        for(const auto& [real,imag]: nyquist(B.sweep(0,10000))){
            outCSV<<std::fixed<<std::setprecision(15)<<real<<','<<imag<<'\n';
        }
    }

    {
        std::ofstream outCSV("./data/bode.csv");

        std::map<double,std::complex<double>> sweep = B.sweep(0,1000);

        for(const auto& [freq,mag]: bode(sweep)){
            outCSV<<std::fixed<<std::setprecision(15)<<freq<<','<<mag<<'\n';
        }

        outCSV.close();

        outCSV.open("./data/bodePhase.csv");

        for(const auto& [freq,Z]: sweep){
            outCSV<<std::fixed<<std::setprecision(15)<<freq<<','<<20*log10(abs(Z))<<','<<arg(Z)<<'\n';
        }
    }

    return 0;
}
