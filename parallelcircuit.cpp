#include "logic.h"
#include <cmath>

namespace Circuits {

void ParallelCircuit::add(std::shared_ptr<Component> comp) {
    subcomponents_.push_back(comp); // is this boilerplate code that I looked up a tutorial for? yes. 
}

/**
    Mathematical Background:
    In a parallel circuit, every element has the same voltage V across its terminals. By Kirchhoff's
    Current Law:
    I_total = Sigma_i I_i  (the total current entering the node equals the sum of branch currents)

    Since each branch obeys Ohm's law (I_i = V / Z_i), we can factor out the common voltage V:
    I_total = V * (1/Z_1 + 1/Z_2 + ... + 1/Z_n)

    The quantity Y = 1/Z is called admittance. For parallel circuits:
    Y_parallel = Sigma_i Y_i  ->  Z_parallel = 1 / (Sigma_i 1/Z_i)

    This is the dual of the series rule and makes solving parallel networks straightforward.
**/
void ParallelCircuit::printType() const {
    std::cout << "ParallelCircuit(" << subcomponents_.size() << " components)" << std::endl;
}

/**
    Mathematical Background:
    The equivalent impedance of a parallel circuit is found by summing branch admittances (reciprocals).

    Y_total(f) = Sigma_i (1 / Z_i(f))  where Z_i = R_i + j*X_i  and  Y_i = G_i + jB_i
    Z_parallel(f) = 1 / Y_total(f)

    Each branch's impedance is evaluated at the same angular frequency w = 2pif, then its reciprocal
    (admittance in siemens) is summed. If any single branch has zero impedance, which is a short circuit -
    the entire parallel network goes down to to Z = 0 regardless of other branches. Similarly, if total
    admittance approaches zero (e.g., every element behaves as an open circuit), we return zero rather
    than risk divergence from division by zero.
**/
std::complex<double> ParallelCircuit::impedance(double frequency) const {
    std::complex<double> admittance(0.0, 0.0);
    for (const auto& comp : subcomponents_) {
        std::complex<double> z = comp->impedance(frequency);
        if (std::abs(z) < 1e-20) {
            // If any branch has zero impedance, total is zero
            return std::complex<double>(0.0, 0.0);
        }
        admittance += 1.0 / z;
    }
    if (std::abs(admittance) < 1e-20) {
        return std::complex<double>(0.0, 0.0);
    }
    return 1.0 / admittance;
}

/**
    Mathematical Background (real power dissipated by a parallel network):
    Since voltage is common across all branches, we first compute the total voltage magnitude:
      V = I_total * |Z_parallel|

    Then use current division to find each branch's share of the total current:
      I_i     = V / |Z_i|

    Individual power losses are summed:
      P_total = Sigma_i I_i^2 * R_i  (= Sigma_i comp->powerLoss(I_i))

    Equivalently, using admittance form:  P_total = Sigma_i V^2 * Re{Y_i}

    Reactive elements (e.g. capacitors, inductors) contribute zero real power; only resistive
    branches dissipate energy as heat. The phase angle fi between voltage and current in each
    branch determines the fraction of apparent power that becomes real power:
      P_avg = V_rms * I_rms * cos(fi)
**/
double ParallelCircuit::powerLoss(double current) const {
    std::complex<double> zTotal = impedance(50.0);

    // V = I * |Z| gives the magnitude of voltage across the parallel combination
    double vMag = current * std::abs(zTotal);

    // For each subcomponent, compute I_i = V / |Z_i| and sum power losses
    double totalPower = 0.0;
    for (const auto& comp : subcomponents_) {
        std::complex<double> zComp = comp->impedance(50.0);
        if (std::abs(zComp) < 1e-20) continue;

        double iMag = vMag / std::abs(zComp);
        totalPower += comp->powerLoss(iMag);
    }

    return totalPower;
}

}