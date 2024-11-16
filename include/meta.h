#ifndef LAB_H
#define LAB_H

#include <iostream>
#include <memory>
#include <utility>

// Шаблонная структура для точки
template <typename T>
class Point {
private:
    T x, y;
public:
    Point(T x = 0, T y = 0);
    T getX() const;
    T getY() const;
    void setX(T x);
    void setY(T y);
    void print(std::ostream& os) const;
};

// Шаблонный базовый класс для фигур
template <typename T>
class Figure {
public:
    virtual ~Figure() = default;
    virtual std::pair<T, T> center() const = 0;
    virtual void print(std::ostream& os) const = 0;
    virtual void read(std::istream& is) = 0;
    virtual operator double() const = 0;
    virtual bool operator==(const Figure<T>& other) const = 0;
};

// Шаблонный класс для трапеции
template <typename T>
class Trapecia : public Figure<T> {
private:
    T a, b, h;
    std::unique_ptr<Point<T>> vertices[4];
public:
    Trapecia(T a = 1, T b = 1, T h = 1);
    std::pair<T, T> center() const override;
    void print(std::ostream& os) const override;
    void read(std::istream& is) override;
    operator double() const override;
    bool operator==(const Figure<T>& other) const override;
    Trapecia& operator=(const Trapecia<T>& other);
    Trapecia& operator=(Trapecia<T>&& other) noexcept;
};

// Шаблонный класс для ромба
template <typename T>
class Romb : public Figure<T> {
private:
    T d1, d2;
    std::unique_ptr<Point<T>> vertices[4];
public:
    Romb(T d1 = 1, T d2 = 1);
    std::pair<T, T> center() const override;
    void print(std::ostream& os) const override;
    void read(std::istream& is) override;
    operator double() const override;
    bool operator==(const Figure<T>& other) const override;
    Romb& operator=(const Romb<T>& other);
    Romb& operator=(Romb<T>&& other) noexcept;
};

// Шаблонный класс для правильного пятиугольника
template <typename T>
class Penta : public Figure<T> {
private:
    T side;
    std::unique_ptr<Point<T>> vertices[5];
public:
    Penta(T side = 1);
    std::pair<T, T> center() const override;
    void print(std::ostream& os) const override;
    void read(std::istream& is) override;
    operator double() const override;
    bool operator==(const Figure<T>& other) const override;
    Penta& operator=(const Penta<T>& other);
    Penta& operator=(Penta<T>&& other) noexcept;
};

#endif // LAB_H
