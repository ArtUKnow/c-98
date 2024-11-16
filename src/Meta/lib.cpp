#include "../../include/meta.h"

// Реализация DynamicArray
template <typename T>
DynamicArray<T>::DynamicArray() : size(0), capacity(10) {
    data = std::shared_ptr<T[]>(new T[capacity]);
}

template <typename T>
void DynamicArray<T>::addFigure(const T& value) {
    if (size == capacity) {
        resize(capacity * 2);
    }
    data[size++] = value;
}

template <typename T>
void DynamicArray<T>::removeFigure(size_t index) {
    if (index >= size) {
        throw std::out_of_range("Index out of range");
    }
    for (size_t i = index; i < size - 1; ++i) {
        data[i] = data[i + 1];
    }
    --size;
}

template <typename T>
T& DynamicArray<T>::operator[](size_t index) {
    if (index >= size) {
        throw std::out_of_range("Index out of range");
    }
    return data[index];
}

template <typename T>
size_t DynamicArray<T>::getSize() const {
    return size;
}

template <typename T>
void DynamicArray<T>::printFigures() const {
    for (size_t i = 0; i < size; ++i) {
        data[i]->print(std::cout);
    }
}

template <typename T>
double DynamicArray<T>::totalArea() const {
    double total = 0.0;
    for (size_t i = 0; i < size; ++i) {
        total += static_cast<double>(*data[i]);
    }
    return total;
}

template <typename T>
void DynamicArray<T>::resize(size_t new_capacity) {
    std::shared_ptr<T[]> new_data(new T[new_capacity]);
    for (size_t i = 0; i < size; ++i) {
        new_data[i] = data[i];
    }
    data = new_data;
    capacity = new_capacity;
}

// Реализация Trapecia
template <Scalar T>
std::unique_ptr<Point<T>> Trapecia<T>::center() const {
    return std::make_unique<Point<T>>(0, h / 2);
}

template <Scalar T>
void Trapecia<T>::print(std::ostream& os) const {
    os << "Trapecia with a = " << a << ", b = " << b << ", h = " << h << "\n";
}

template <Scalar T>
void Trapecia<T>::read(std::istream& is) {
    is >> a >> b >> h;
}

template <Scalar T>
Trapecia<T>::operator double() const {
    return (a + b) * h / 2.0;
}

template <Scalar T>
bool Trapecia<T>::operator==(const Figure<T>& other) const {
    const Trapecia<T>* o = dynamic_cast<const Trapecia<T>*>(&other);
    return o && a == o->a && b == o->b && h == o->h;
}

// Реализация Romb
template <Scalar T>
std::unique_ptr<Point<T>> Romb<T>::center() const {
    return std::make_unique<Point<T>>(0, 0);
}

template <Scalar T>
void Romb<T>::print(std::ostream& os) const {
    os << "Romb with diagonals d1 = " << d1 << ", d2 = " << d2 << "\n";
}

template <Scalar T>
void Romb<T>::read(std::istream& is) {
    is >> d1 >> d2;
}

template <Scalar T>
Romb<T>::operator double() const {
    return (d1 * d2) / 2.0;
}

template <Scalar T>
bool Romb<T>::operator==(const Figure<T>& other) const {
    const Romb<T>* o = dynamic_cast<const Romb<T>*>(&other);
    return o && d1 == o->d1 && d2 == o->d2;
}

// Реализация Penta
template <Scalar T>
std::unique_ptr<Point<T>> Penta<T>::center() const {
    return std::make_unique<Point<T>>(0, 0);
}

template <Scalar T>
void Penta<T>::print(std::ostream& os) const {
    os << "Penta with side = " << side << "\n";
}

template <Scalar T>
void Penta<T>::read(std::istream& is) {
    is >> side;
}

template <Scalar T>
Penta<T>::operator double() const {
    return (5 * side * side) / (4 * tan(M_PI / 5));
}

template <Scalar T>
bool Penta<T>::operator==(const Figure<T>& other) const {
    const Penta<T>* o = dynamic_cast<const Penta<T>*>(&other);
    return o && side == o->side;
}

template class Trapecia<double>;
template class Romb<double>;
template class Penta<double>;
template class DynamicArray<std::shared_ptr<Figure<double>>>;
