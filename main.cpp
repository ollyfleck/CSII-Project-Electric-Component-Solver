#include "logic.h"
#include <iostream>
#include <iomanip>
#include <memory>
#include <string.h>
#include <vector>

int main() {
    // the ac waveform
    double frequency  = 50.0;   // Hz
    double current    = 2.0;    // A

    // basic components: 100 ohm resistor, 10 uF capacitor, 50 mH inductor
    // note for future self: learn how exactly make_shared works its actually pretty useful
    auto r1 = std::make_shared<Circuits::Resistor>(100.0);
    auto r2 = std::make_shared<Circuits::Resistor>(200.0);
    auto c1 = std::make_shared<Circuits::Capacitor>(10e-6);     // 10 uF
    auto l1 = std::make_shared<Circuits::Inductor>(50e-3);      // 50 mH

    std::cout << "R1 impedance real " << std::to_string(r1->impedance(frequency).real()) << std::endl;
    std::cout << "R1 impedance imag " << std::to_string(r1->impedance(frequency).imag()) << std::endl; // should be 0

    std::cout << "C1 impedance read " << std::to_string(c1->impedance(frequency).real()) << std::endl; // should be 0
    std::cout << "C1 impedance imag " << std::to_string(c1->impedance(frequency).imag()) << std::endl;

    std::cout << "L1 impedance real " << std::to_string(l1->impedance(frequency).real()) << std::endl; // should be 0
    std::cout << "L1 impedance imag " << std::to_string(l1->impedance(frequency).imag()) << std::endl;

    return 0;
}