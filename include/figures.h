#ifndef LAB_H
#define LAB_H

#include <iostream>
#include <cmath>
#include <utility>

class Figure {
public:
    virtual ~Figure() {}
    virtual std::pair<double, double> center() const = 0;
    virtual void print(std::ostream& os) const = 0;
    virtual void read(std::istream& is) = 0;
    virtual operator double() const = 0;
    virtual bool operator==(const Figure& other) const = 0;
    virtual Figure& operator=(const Figure &other) = 0;
    virtual Figure& operator=(Figure &&other) = 0;
};

class Trapecia : public Figure {
private:
    double a, b, h;

public:
    Trapecia(double a = 1, double b = 1, double h = 1) : a(a), b(b), h(h) {}
    std::pair<double, double> center() const override;
    void print(std::ostream& os) const override;
    void read(std::istream& is) override;
    operator double() const override;
    bool operator==(const Figure& other) const override;
    Figure& operator=(const Figure& other) override;
    Figure& operator=(Figure&& other) override;
};

class Romb : public Figure {
private:
    double d1, d2;

public:
    Romb(double d1 = 1, double d2 = 1) : d1(d1), d2(d2) {}
    std::pair<double, double> center() const override;
    void print(std::ostream& os) const override;
    void read(std::istream& is) override;
    operator double() const override;
    bool operator==(const Figure& other) const override;
    Figure& operator=(const Figure& other) override;
    Figure& operator=(Figure&& other) override;
};

class Penta : public Figure {
private:
    double side;

public:
    Penta(double side = 1) : side(side) {}
    Penta(const Penta& other) : side(other.side) {}
    Penta(Penta&& other) noexcept : side(other.side) {}
    std::pair<double, double> center() const override;
    void print(std::ostream& os) const override;
    void read(std::istream& is) override;
    operator double() const override;
    bool operator==(const Figure& other) const override;
    Figure& operator=(const Figure& other) override;
    Figure& operator=(Figure&& other) override;
};
std::ostream& operator<<(std::ostream& os, const Figure& figure);
std::istream& operator>>(std::istream& is, Figure& figure);

#endif
