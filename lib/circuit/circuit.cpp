#include "circuit.h"

bool Impedance::simplify(double freq){
    if(R!=0){
        real = R;
    }
    else if(L!=0){
        imag = freq*L;
    }
    else if(C!=0){
        imag = -1/(freq*C);
    }

    mag = sqrt(real*real+imag*imag);
    phase = atan(imag/real);
}

bool Circuit::simplify(double freq){
    for(auto& series: components){
        for(auto& parallel: series){
            parallel->simplify(freq);
        }
    }
}
