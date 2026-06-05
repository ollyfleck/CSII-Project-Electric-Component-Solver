#include "logic.h"

// a lot of this is copied from parallelcircuit.cpp, since the structure is fairly similar, just that the math is different.

namespace Circuits {

void SeriesCircuit::add(std::shared_ptr<Component> comp) {
    subcomponents_.push_back(comp);
}

/**
    Mathematical Background:
    In a series circuit, the same current I flows through every component. By Kirchhoff's Voltage Law:
    V_total = Sigma V_i  (the total voltage is the phasor sum of individual voltages)

    Since each branch obeys Ohm's law (V_i = I * Z_i), we can factor out the common current I:
    V_total = I * (Z_1 + Z_2 + ... + Z_n)

    Therefore, for components connected in series, the equivalent impedance is simply:
    Z_series = Sigma_i Z_i   (complex sum of all impedances)
**/
void SeriesCircuit::printType() const {
    std::cout << "SeriesCircuit(" << subcomponents_.size() << " components)" << std::endl;
}

/**
    Mathematical Background:
    The equivalent impedance of a series circuit is the phasor (complex) sum of all branch impedances.

    Z_series(f) = Sigma_i Z_i(f)

    Each subcomponent's impedance is evaluated at the same angular frequency w = 2pif, then added
    as complex numbers - the real parts (resistive) and imaginary parts (reactive) add independently:
      Z_series = (Sigma R_i) + j * (Sigma X_i)

    This follows directly from KVL: if every element carries current I, the total voltage is
    V_total = Sigma(I * Z_i) = I * Sigma Z_i  ->  Z_eq = V_total / I = Sigma Z_i
**/
std::complex<double> SeriesCircuit::impedance(double frequency) const {
    std::complex<double> total(0.0, 0.0);
    for (const auto& comp : subcomponents_) {
        total += comp->impedance(frequency);
    }
    return total;
}

/**
    Mathematical Background (real power dissipated by a series network):
    P_total = Sigma_i I_rms^2 * R_i  (= I_rms^2 * Sigma R_i)
           (= I_rms^2 * Re{Z_series})

    Since the same current flows through every element in series, each component dissipates power
    independently and the total is just their sum. Reactive elements (capacitors, inductors) contribute
    P = 0 W; only resistive components convert electrical energy into heat:
      P_avg = V_rms * I_rms * cos(fi), where fi is the phase angle of each element

    For a pure resistor: fi = 0deg -> P = I^2 * R.
    For an ideal capacitor or inductor: fi = ±90deg -> P = 0.
**/
double SeriesCircuit::powerLoss(double current, double frequency) const {
    double total = 0.0;
    for (const auto& comp : subcomponents_) {
        total += comp->powerLoss(current, frequency);
    }
    return total;
}

}
