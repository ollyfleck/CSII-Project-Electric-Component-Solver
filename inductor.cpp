#include "logic.h"

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

// most of this is actually copied from capacitor.cpp since it's the exact same stuff but in reverse

namespace Circuits {

Inductor::Inductor(double value) : value_(value) {
    if (value < 0.0) {
        std::cerr << "[error] Inductance cannot be negative - given: " << value << "\n";
    }
}

/**
    Mathematical Background:
    An ideal inductor is a purely reactive element, it stores energy in its magnetic
    field during one half-cycle and returns it to the circuit during the other half-cycle.
    The phase angle between voltage and current is exactly +90deg, so the impedance is purely imaginary:
    Z_L(f) = j * wL  where  w = 2pif

    Because voltage always leads current by a quarter cycle:
    P_avg = V_rms * I_rms * cos(90deg) = V * I * cos(pi/2) = 0

    The frequency dependence looks as follows:
    Z_L(f) = j * (2pif) * L

    At f = 0 (basically DC), Z_L is zero, which means it's a short circuit.
    As f goes to infinity, Z_L goes to infinity, which means it's an open circuit.
**/

void Inductor::printType() const {
    std::cout << "Inductor(" << value_ << " H)" << std::endl;
}

std::complex<double> Inductor::impedance(double frequency) const {
    if (frequency == 0.0) { // avoid division by zero, at an f of 0 we know that the inductor will be a short circuit
        return std::complex<double>(0.0, 1e20);
    }
    return std::complex<double>(0.0, 2.0 * M_PI * frequency * value_);
}

double Inductor::powerLoss(double current, double frequency) const {
    return 0.0;  // ideal inductor has no real power loss
}

}
