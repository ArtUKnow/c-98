#ifndef LAB_H
#define LAB_H

#include <iostream>
#include <cmath>
#include <memory>
#include <utility>
#include <type_traits>

template <typename T>
concept Scalar = std::is_arithmetic_v<T>;

template <Scalar T>
class Point {
public:
    T x, y;

    Point(T x = 0, T y = 0) : x(x), y(y) {}
    void print(std::ostream& os) const {
        os << x << y;
    }
};

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

template <typename T>
class Array {
private:
    std::shared_ptr<T[]> data;
    size_t size;
    size_t capacity;

    void resize();

public:
    Array();
    void add(const T& element);
    void remove(size_t index);
    size_t getSize() const;
    T& operator[](size_t index);
    const T& operator[](size_t index) const;
};

#endif
