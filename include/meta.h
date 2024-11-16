#ifndef FIGURES_H
#define FIGURES_H

#include <iostream>
#include <cmath>
#include <memory>
#include <concepts>

// Концепт для проверки скалярного типа
template <typename T>
concept Scalar = std::is_arithmetic_v<T>;

// Шаблонная структура точки
template <Scalar T>
struct Point {
    T x, y;
    Point(T x = 0, T y = 0) : x(x), y(y) {}
};

// Базовый класс фигуры
template <Scalar T>
class Figure {
public:
    virtual ~Figure() {}
    virtual std::unique_ptr<Point<T>> center() const = 0;
    virtual void print(std::ostream& os) const = 0;
    virtual void read(std::istream& is) = 0;
    virtual operator double() const = 0;
    virtual bool operator==(const Figure& other) const = 0;
};

// Трапеция
template <Scalar T>
class Trapecia : public Figure<T> {
private:
    T a, b, h;

public:
    Trapecia(T a = 1, T b = 1, T h = 1) : a(a), b(b), h(h) {}
    std::unique_ptr<Point<T>> center() const override;
    void print(std::ostream& os) const override;
    void read(std::istream& is) override;
    operator double() const override;
    bool operator==(const Figure<T>& other) const override;
};

// Ромб
template <Scalar T>
class Romb : public Figure<T> {
private:
    T d1, d2;

public:
    Romb(T d1 = 1, T d2 = 1) : d1(d1), d2(d2) {}
    std::unique_ptr<Point<T>> center() const override;
    void print(std::ostream& os) const override;
    void read(std::istream& is) override;
    operator double() const override;
    bool operator==(const Figure<T>& other) const override;
};

// Пятиугольник
template <Scalar T>
class Penta : public Figure<T> {
private:
    T side;

public:
    Penta(T side = 1) : side(side) {}
    std::unique_ptr<Point<T>> center() const override;
    void print(std::ostream& os) const override;
    void read(std::istream& is) override;
    operator double() const override;
    bool operator==(const Figure<T>& other) const override;
};

// Шаблон динамического массива
template <typename T>
class DynamicArray {
private:
    std::shared_ptr<T[]> data;
    size_t size;
    size_t capacity;

public:
    DynamicArray();
    void addFigure(const T& value);
    void removeFigure(size_t index);
    T& operator[](size_t index);
    size_t getSize() const;
    size_t getCapacity() const;
    void printFigures() const;
    double totalArea() const;

private:
    void resize(size_t new_capacity);
};

#endif
