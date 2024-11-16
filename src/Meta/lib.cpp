#include "../../include/meta.h"
#include <cmath>
#include <iostream>

// Реализация шаблона Point
template <typename T>
Point<T>::Point(T x, T y) : x(x), y(y) {}

template <typename T>
T Point<T>::getX() const {
    return x;
}

template <typename T>
T Point<T>::getY() const {
    return y;
}

template <typename T>
void Point<T>::setX(T x) {
    this->x = x;
}

template <typename T>
void Point<T>::setY(T y) {
    this->y = y;
}

template <typename T>
void Point<T>::print(std::ostream& os) const {
    os << "(" << x << ", " << y << ")";
}

// Реализация классов Trapecia, Romb и Penta
template <typename T>
Trapecia<T>::Trapecia(T a, T b, T h) : a(a), b(b), h(h) {
    vertices[0] = std::make_unique<Point<T>>(0, 0);
    vertices[1] = std::make_unique<Point<T>>(a, 0);
    vertices[2] = std::make_unique<Point<T>>((a - b) / 2, h);
    vertices[3] = std::make_unique<Point<T>>((a + b) / 2, h);
}

template <typename T>
std::pair<T, T> Trapecia<T>::center() const {
    return {(vertices[0]->getX() + vertices[1]->getX() + vertices[2]->getX() + vertices[3]->getX()) / 4,
            (vertices[0]->getY() + vertices[1]->getY() + vertices[2]->getY() + vertices[3]->getY()) / 4};
}

template <typename T>
void Trapecia<T>::print(std::ostream& os) const {
    os << "Trapecia with vertices: ";
    for (const auto& vertex : vertices) {
        vertex->print(os);
        os << " ";
    }
}

template <typename T>
void Trapecia<T>::read(std::istream& is) {
    is >> a >> b >> h;
    vertices[0] = std::make_unique<Point<T>>(0, 0);
    vertices[1] = std::make_unique<Point<T>>(a, 0);
    vertices[2] = std::make_unique<Point<T>>((a - b) / 2, h);
    vertices[3] = std::make_unique<Point<T>>((a + b) / 2, h);
}

template <typename T>
Trapecia<T>::operator double() const {
    return (static_cast<double>(a + b) * h) / 2.0;
}

template <typename T>
bool Trapecia<T>::operator==(const Figure<T>& other) const {
    const auto* op = dynamic_cast<const Trapecia<T>*>(&other);
    return op && a == op->a && b == op->b && h == op->h;
}

template <typename T>
Trapecia<T>& Trapecia<T>::operator=(const Trapecia<T>& other) {
    if (this == &other) return *this;
    a = other.a;
    b = other.b;
    h = other.h;
    vertices[0] = std::make_unique<Point<T>>(*other.vertices[0]);
    vertices[1] = std::make_unique<Point<T>>(*other.vertices[1]);
    vertices[2] = std::make_unique<Point<T>>(*other.vertices[2]);
    vertices[3] = std::make_unique<Point<T>>(*other.vertices[3]);
    return *this;
}

template <typename T>
Trapecia<T>& Trapecia<T>::operator=(Trapecia<T>&& other) noexcept {
    if (this == &other) return *this;
    a = std::move(other.a);
    b = std::move(other.b);
    h = std::move(other.h);
    vertices[0] = std::move(other.vertices[0]);
    vertices[1] = std::move(other.vertices[1]);
    vertices[2] = std::move(other.vertices[2]);
    vertices[3] = std::move(other.vertices[3]);
    return *this;
}

template <typename T>
Romb<T>::Romb(T d1, T d2) : d1(d1), d2(d2) {
    vertices[0] = std::make_unique<Point<T>>(0, d2 / 2);
    vertices[1] = std::make_unique<Point<T>>(d1 / 2, 0);
    vertices[2] = std::make_unique<Point<T>>(0, -d2 / 2);
    vertices[3] = std::make_unique<Point<T>>(-d1 / 2, 0);
}

template <typename T>
std::pair<T, T> Romb<T>::center() const {
    return {0, 0};
}

template <typename T>
void Romb<T>::print(std::ostream& os) const {
    os << "Romb with vertices: ";
    for (const auto& vertex : vertices) {
        vertex->print(os);
        os << " ";
    }
}

template <typename T>
void Romb<T>::read(std::istream& is) {
    is >> d1 >> d2;
    vertices[0] = std::make_unique<Point<T>>(0, d2 / 2);
    vertices[1] = std::make_unique<Point<T>>(d1 / 2, 0);
    vertices[2] = std::make_unique<Point<T>>(0, -d2 / 2);
    vertices[3] = std::make_unique<Point<T>>(-d1 / 2, 0);
}

template <typename T>
Romb<T>::operator double() const {
    return (static_cast<double>(d1) * d2) / 2.0;
}

template <typename T>
bool Romb<T>::operator==(const Figure<T>& other) const {
    const auto* op = dynamic_cast<const Romb<T>*>(&other);
    return op && d1 == op->d1 && d2 == op->d2;
}

template <typename T>
Romb<T>& Romb<T>::operator=(const Romb<T>& other) {
    if (this == &other) return *this;
    d1 = other.d1;
    d2 = other.d2;
    vertices[0] = std::make_unique<Point<T>>(*other.vertices[0]);
    vertices[1] = std::make_unique<Point<T>>(*other.vertices[1]);
    vertices[2] = std::make_unique<Point<T>>(*other.vertices[2]);
    vertices[3] = std::make_unique<Point<T>>(*other.vertices[3]);
    return *this;
}

template <typename T>
Romb<T>& Romb<T>::operator=(Romb<T>&& other) noexcept {
    if (this == &other) return *this;
    d1 = std::move(other.d1);
    d2 = std::move(other.d2);
    vertices[0] = std::move(other.vertices[0]);
    vertices[1] = std::move(other.vertices[1]);
    vertices[2] = std::move(other.vertices[2]);
    vertices[3] = std::move(other.vertices[3]);
    return *this;
}

template <typename T>
Penta<T>::Penta(T side) : side(side) {
    for (int i = 0; i < 5; ++i) {
        double angle = 2 * M_PI * i / 5;
        vertices[i] = std::make_unique<Point<T>>(side * cos(angle), side * sin(angle));
    }
}

template <typename T>
std::pair<T, T> Penta<T>::center() const {
    return {0, 0};
}

template <typename T>
void Penta<T>::print(std::ostream& os) const {
    os << "Penta with vertices: ";
    for (const auto& vertex : vertices) {
        vertex->print(os);
        os << " ";
    }
}

template <typename T>
void Penta<T>::read(std::istream& is) {
    is >> side;
    for (int i = 0; i < 5; ++i) {
        double angle = 2 * M_PI * i / 5;
        vertices[i] = std::make_unique<Point<T>>(side * cos(angle), side * sin(angle));
    }
}

template <typename T>
Penta<T>::operator double() const {
    return (5 * static_cast<double>(side) * side) / (4 * tan(M_PI / 5));
}

template <typename T>
bool Penta<T>::operator==(const Figure<T>& other) const {
    const auto* op = dynamic_cast<const Penta<T>*>(&other);
    return op && side == op->side;
}

template <typename T>
Penta<T>& Penta<T>::operator=(const Penta<T>& other) {
    if (this == &other) return *this;
    side = other.side;
    for (int i = 0; i < 5; ++i) {
        vertices[i] = std::make_unique<Point<T>>(*other.vertices[i]);
    }
    return *this;
}

template <typename T>
Penta<T>& Penta<T>::operator=(Penta<T>&& other) noexcept {
    if (this == &other) return *this;
    side = std::move(other.side);
    for (int i = 0; i < 5; ++i) {
        vertices[i] = std::move(other.vertices[i]);
    }
    return *this;
}
