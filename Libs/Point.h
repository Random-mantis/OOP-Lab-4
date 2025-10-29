#pragma once
#include <iostream>
#include <concepts>
#include <type_traits>
#include "Scalar.h"

template <Scalar T>
struct Point {
private:
    T x{};
    T y{};
public:
    Point() = default;
    Point(T x, T y) : x{x}, y{y} {}
    ~Point() = default;

    bool operator==(const Point& other) const noexcept { return x == other.x && y == other.y; }
    bool operator!=(const Point& other) const noexcept { return !(*this == other); }

    friend std::ostream& operator<<(std::ostream& os, const Point& p) {
        return os << "(" << p.x << ", " << p.y << ")";
    }

    friend std::istream& operator>>(std::istream& is, Point& p) {
        return is >> p.x >> p.y;
    }

    T getx() const noexcept { return x; }
    T gety() const noexcept { return y; }

    void setx(T new_x) noexcept { x = new_x; }
    void sety(T new_y) noexcept { y = new_y; }
};