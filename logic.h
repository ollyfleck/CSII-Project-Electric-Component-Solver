#pragma once
// awful and evil. ughhhh. why did it take me so long to figure out

#include <cmath>
#include <complex>
#include <iostream>
#include <memory>
#include <string>
#include <vector>

namespace Circuits {

class Component;  // forward declaration

// base class

class Component {
public:
    virtual ~Component() = default;

    virtual void printType() const = 0;
    virtual std::complex<double> impedance(double frequency) const = 0;
    virtual double powerLoss(double current) const = 0;
};

// basic comps

class Resistor : public Component {
private:
    double value_;                       // resistance in ohms
public:
    explicit Resistor(double value);
    void printType() const override;
    std::complex<double> impedance(double frequency) const override;
    double powerLoss(double current) const override;
};

class Capacitor : public Component {
private:
    double value_;                       // capacitance in farads
public:
    explicit Capacitor(double value);
    void printType() const override;
    std::complex<double> impedance(double frequency) const override;
    double powerLoss(double current) const override;
};

class Inductor : public Component {
private:
    double value_;                       // inductance in henries
public:
    explicit Inductor(double value);
    void printType() const override;
    std::complex<double> impedance(double frequency) const override;
    double powerLoss(double current) const override;
};

}