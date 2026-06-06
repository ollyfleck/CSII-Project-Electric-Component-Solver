#include "logic.h"

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

/**
    Mathematical Background:
    An ideal capacitor is a purely reactive element, it stores energy in its electric
    field during one half-cycle and returns it to the circuit during the other half-cycle.
    The phase angle between voltage and current is exactly -90deg, so:
    P_avg = V_rms * I_rms * cos(fi) = V*I*cos(-pi/2) = 0

    The frequency dependence looks as follows:
    Z_C(f) = -j * (1 / wC)
    where
    w = 2pif

    At f = 0 (basically DC), Z_C is infinite, which means it's an open circuit.
    As f goes to infinity, Z_C goes to 0, which means it's a short circuit.
**/

namespace Circuits {

Capacitor::Capacitor(double value) : value_(value) {
    if (value < 0.0) {
        std::cerr << "[error] Capacitance cannot be negative - given: " << value << "\n";
    }
}

void Capacitor::printType() const {
    std::cout << "Capacitor(" << value_ << " F)" << std::endl;
}

std::complex<double> Capacitor::impedance(double frequency) const {
    if (frequency == 0.0) { // avoid division by zero, at an f of 0 we know that the cap will be an open circuit
        return std::complex<double>(0.0, -1e20); // 1e20 as a stand-in for infinity because numeric_limits<int>::infinity() has issues with complex types and wow this is a nightmare
    }
    return std::complex<double>(0.0, -1 / (2.0 * M_PI * frequency * value_));
}

double Capacitor::powerLoss(double current_, double frequency_) const { // these parameters are unused but I don't think anybody will care
    (void)frequency_;
    (void)current_;
    return 0.0;  // ideal capacitor has no real power loss, since resistance between the plates is ideally infinite
}

}