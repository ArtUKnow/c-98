#include "lab.h"

// Реализация Trapecia
template <Scalar T>
std::unique_ptr<Point<T>> Trapecia<T>::center() const {
    return std::make_unique<Point<T>>((a + b) / 2, h / 2);
}

template <Scalar T>
void Trapecia<T>::print(std::ostream& os) const {
    os << "Trapecia: a=" << a << ", b=" << b << ", h=" << h;
}

template <Scalar T>
void Trapecia<T>::read(std::istream& is) {
    is >> a >> b >> h;
}

template <Scalar T>
Trapecia<T>::operator double() const {
    return static_cast<double>((a + b) * h / 2);
}

template <Scalar T>
bool Trapecia<T>::operator==(const Figure<T>& other) const {
    const Trapecia<T>* o = dynamic_cast<const Trapecia<T>*>(&other);
    return o != nullptr && a == o->a && b == o->b && h == o->h;
}

// Реализация Romb
template <Scalar T>
std::unique_ptr<Point<T>> Romb<T>::center() const {
    return std::make_unique<Point<T>>(d1 / 2, d2 / 2);
}

template <Scalar T>
void Romb<T>::print(std::ostream& os) const {
    os << "Romb: d1=" << d1 << ", d2=" << d2;
}

template <Scalar T>
void Romb<T>::read(std::istream& is) {
    is >> d1 >> d2;
}

template <Scalar T>
Romb<T>::operator double() const {
    return static_cast<double>((d1 * d2) / 2);
}

template <Scalar T>
bool Romb<T>::operator==(const Figure<T>& other) const {
    const Romb<T>* o = dynamic_cast<const Romb<T>*>(&other);
    return o != nullptr && d1 == o->d1 && d2 == o->d2;
}

// Реализация Penta
template <Scalar T>
std::unique_ptr<Point<T>> Penta<T>::center() const {
    T angle = 2 * M_PI / 5;
    return std::make_unique<Point<T>>(side * std::cos(angle), side * std::sin(angle));
}

template <Scalar T>
void Penta<T>::print(std::ostream& os) const {
    os << "Penta: side=" << side;
}

template <Scalar T>
void Penta<T>::read(std::istream& is) {
    is >> side;
}

template <Scalar T>
Penta<T>::operator double() const {
    return static_cast<double>(5 * side * side / (4 * std::tan(M_PI / 5)));
}

template <Scalar T>
bool Penta<T>::operator==(const Figure<T>& other) const {
    const Penta<T>* o = dynamic_cast<const Penta<T>*>(&other);
    return o != nullptr && side == o->side;
}

// Реализация Array
template <typename T>
Array<T>::Array() : size(0), capacity(1) {
    data = std::shared_ptr<T[]>(new T[capacity]);
}

template <typename T>
void Array<T>::resize() {
    capacity *= 2;
    std::shared_ptr<T[]> newData(new T[capacity]);
    for (size_t i = 0; i < size; ++i) {
        newData[i] = std::move(data[i]);
    }
    data = std::move(newData);
}

template <typename T>
void Array<T>::add(const T& element) {
    if (size == capacity) {
        resize();
    }
    data[size++] = element;
}

template <typename T>
void Array<T>::remove(size_t index) {
    if (index >= size) return;
    for (size_t i = index; i < size - 1; ++i) {
        data[i] = std::move(data[i + 1]);
    }
    --size;
}

template <typename T>
size_t Array<T>::getSize() const {
    return size;
}

template <typename T>
T& Array<T>::operator[](size_t index) {
    return data[index];
}

template <typename T>
const T& Array<T>::operator[](size_t index) const {
    return data[index];
}
