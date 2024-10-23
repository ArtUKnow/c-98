#include "../../include/figures.h"

// Трапеция 

std::pair<double, double> Trapecia::center() const {
    if (a == 0 && b ==0 && h == 0){
        return {0, 0};
    }
    return {(a+2*b)/(3*(a+b))*h, h / 3};
}

void Trapecia::print(std::ostream& os) const {
    os << a<<b<<h;
}

void Trapecia::read(std::istream& is) {
    is >> a>>b >>h;
}

Trapecia::operator double() const {
    return ((a + b)* h)/2.0;
}

bool Trapecia::operator==(const Figure& other) const {
    const Trapecia* op= dynamic_cast<const Trapecia*>(&other);
    return op && a == op->a && b == op->b && h == op->h;
}

Figure& Trapecia::operator=(const Figure& other) {
    if (this == &other) return *this;
    const Trapecia* op= dynamic_cast<const Trapecia*>(&other);
    if (op) {
        a = op->a;
        b = op->b;
        h = op->h;
    }
    return *this;
}

Figure& Trapecia::operator=(Figure&& other) {
    if (this == &other) return *this;
    Trapecia* op = dynamic_cast<Trapecia*>(&other);
    if (op) {
        a = op->a;
        b = op->b;
        h = op->h;
    }
    return *this;
}





// Ромб

std::pair<double, double> Romb::center() const {
    return {d1 / 2.0, d2 / 2.0}; 
}

void Romb::print(std::ostream& os) const {
    os<< d1 << d2;
}

void Romb::read(std::istream& is) {
    is >>d1 >> d2;
}

Romb::operator double() const {
    return (d1 * d2)/2.0;
}

bool Romb::operator==(const Figure& other) const {
    const Romb* op= dynamic_cast<const Romb*>(&other);
    return op&& d1== op->d1 && d2 == op->d2;
}

Figure& Romb::operator=(const Figure& other) {
    if(this == &other){
        return *this;
    }
    const Romb* op=dynamic_cast<const Romb*>(&other);
    if(op){
        d1 = op->d1;
        d2 = op->d2;
    }
    return *this;
}

Figure& Romb::operator=(Figure&& other) {
    if(this ==&other){
        return *this;
    }
    Romb* op= dynamic_cast<Romb*>(&other);
    if (op) {
        d1 = op->d1;
        d2 = op->d2;
    }
    return *this;
}




// Пятиугольник

std::pair<double, double> Penta::center() const {
    if (side == 0){
        return {0, 0};
    }
    double x = (5.0 / 2.0) * side * cos(M_PI / 5);
    double y = (5.0 / 2.0) * side * sin(M_PI / 5);
    return {x, y};
}

void Penta::print(std::ostream& os) const {
    os << side;
}

void Penta::read(std::istream& is) {
    is >> side;
}

Penta::operator double() const {
    return (5 * side * side) / (4 * tan(M_PI / 5));
}

bool Penta::operator==(const Figure& other) const {
    const Penta* op= dynamic_cast<const Penta*>(&other);
    return op&& side == op->side;
}

Figure& Penta::operator=(const Figure& other) {
    if(this == &other){
        return *this;
    }
    const Penta* op= dynamic_cast<const Penta*>(&other);
    if(op) {
        side = op->side;
    }
    return *this;
}

Figure& Penta::operator=(Figure&& other) {
    if (this == &other){
        return *this;
    } 
    Penta* op= dynamic_cast<Penta*>(&other);
    if(op){
        side = op->side;
    }
    return *this;
}

std::ostream& operator<<(std::ostream& os, const Figure &figure) {
    figure.print(os);
    return os;
}

std::istream& operator>>(std::istream& is, Figure& figure) {
    figure.read(is);
    return is;
}
