#include "logic.h"

namespace Circuits {

Resistor::Resistor(double value) : value_(value) {
    if (value < 0.0) {
        std::cerr << "[error] Resistance cannot be negative - given: " << value << "\n";
    }
}

/**
    Mathematical Background:
    An ideal resistor is a purely dissipative element, it converts electrical energy into heat.
    The phase angle between voltage and current is exactly 0deg, so the impedance is purely real:
    Z_R(f) = R + j * 0
    where R is the resistance in ohms.

    Because voltage and current are always in phase, every half-cycle dissipates energy:
    P_avg = V_rms * I_rms * cos(0) = V * I = I^2 * R

    A resistor's impedance is purely real and independent of frequency.
    It does not store energy, it only dissipates it as heat, so the imaginary part is always zero.
    Z_R(f) = R

    This means at any frequency (DC or AC), the current through a resistor is exactly:
    I(t) = V(t) / R

    And finally, power:
    P_avg = I_rms^2 * R

    Since the voltage across a resistor is V = I*R and both are in phase,
    the instantaneous power p(t) = v(t) * i(t) = i(t)^2 * R always dissipates energy.
    For sinusoidal steady-state with RMS current I: P_avg = I_rms^2 * R
**/
void Resistor::printType() const {
    std::cout << "Resistor(" << value_ << " Ohm)" << std::endl;
}

std::complex<double> Resistor::impedance(double _) const { // don't need frequency. yes. this adds a warning.
    return std::complex<double>(value_, 0.0); // a resistor does not store any energy so the imaginary part is always zero.
}

double Resistor::powerLoss(double current) const {
    return current * current * value_;  // P = I^2 * R
}

}
