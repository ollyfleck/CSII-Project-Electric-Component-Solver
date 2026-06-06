#include "logic.h"
#include <iostream>
#include <iomanip>
#include <vector>

using namespace Circuits;

int main() {
    // the ac waveform
    double frequency  = 50.0;   // Hz
    double current    = 2.0;    // A

    // basic components: 100 ohm resistor, 10 uF capacitor, 50 mH inductor
    Resistor r1(100.0);
    Resistor r2(200.0);
    Capacitor c1(10e-6);     // 10 uF
    Inductor l1(50e-3);      // 50 mH which is actually 0.050000000000000003 according to the debugger. IEEE-754 moment lol

    /*
    std::cout << "R1 impedance real " << std::to_string(r1->impedance(frequency).real()) << std::endl;
    std::cout << "R1 impedance imag " << std::to_string(r1->impedance(frequency).imag()) << std::endl; // should be 0

    std::cout << "C1 impedance read " << std::to_string(c1->impedance(frequency).real()) << std::endl; // should be 0
    std::cout << "C1 impedance imag " << std::to_string(c1->impedance(frequency).imag()) << std::endl;

    std::cout << "L1 impedance real " << std::to_string(l1->impedance(frequency).real()) << std::endl; // should be 0
    std::cout << "L1 impedance imag " << std::to_string(l1->impedance(frequency).imag()) << std::endl;
    */ // why did I even do this, I can just use the debugger lol
    // irrelevant anyway now

    // series RC circuit
    Circuits::SeriesCircuit series;
    series.add(&r1);
    series.add(&c1); // this will add a negative imaginary component to the impedance.

    // parallel RL circuit
    Circuits::ParallelCircuit parallel;
    parallel.add(&l1); // this will add a positive imaginary component to the impedance
    parallel.add(&r2);


    // store the circuits polymorphically. why? the document says so, so sure. 
    std::vector<Circuits::Component*> circuits = {&series, &parallel};

    std::cout << "~~~~ AC Circuit Simulation ~~~~" << std::endl; // hehe get it? cause the ac waveform? ~
    std::cout << "Frequency " << frequency << " Hz\n";
    std::cout << "Total current " << current << " A\n\n";

    for (auto* c : circuits) {
        c->printType();
        std::complex<double> z = c->impedance(frequency);
        double power = c->powerLoss(current, frequency);
        std::cout << "  Impedance      Z = (" << z.real() << ", j" << z.imag() << ") Ohm";
        std::cout << "\n  Power loss     P = " << power << " W\n";
    }

    return 0;
}