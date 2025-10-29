#pragma once
#include <iostream>
#include <concepts>
#include <type_traits>
#include <memory>
#include <cmath>
#include <numbers>
#include "Point.h"
#include "Scalar.h"



template<Scalar T>
class Figure {
protected:
    std::unique_ptr<Point<T>[]> coord{nullptr};
    std::size_t n{0};
public:
    Figure() = default;
    Figure(std::unique_ptr<Point<T>[]>&& p, size_t n) : coord(std::move(p)), n(n) {}
    Figure(std::size_t n) : n(n) { coord = std::make_unique<Point<T>[]>(n); }
    Figure(const Figure& other) : coord(std::make_unique<Point<T>[]>(other.n)), n(other.n) {
        for (std::size_t i = 0; i < n; ++i)
            coord[i] = other.coord[i];
    }
    virtual ~Figure() = default;

    Point<double> centre() const {
        double x = 0.0, y = 0.0;
        for (size_t i = 0; i < n; ++i) {
            x += coord[i].getx();
            y += coord[i].gety();
        }
        return Point<double>(x / n, y / n);
    }

    virtual bool operator==(const Figure& other) const {
        if (n != other.n) return false;
        for (size_t i = 0; i < n; ++i)
            if (coord[i] != other.coord[i]) return false;
        return true;
    }

    virtual bool operator!=(const Figure& other) const { return !(*this == other); }

    virtual Figure& operator=(const Figure& other) {
        if (this == &other) return *this;
        n = other.n;
        auto p = std::make_unique<Point<T>[]>(n);
        for (size_t i = 0; i < n; ++i)
            p[i] = other.coord[i];
        coord = std::move(p);
        return *this;
    }

    friend std::ostream& operator<<(std::ostream& os, const Figure& f) {
        for (size_t i = 0; i < f.n; ++i)
            os << f.coord[i] << " ";
        return os;
    }

    friend std::istream& operator>>(std::istream& is, Figure& f) {
        for (size_t i = 0; i < f.n; ++i)
            is >> f.coord[i];
        return is;
    }

    virtual operator double() const {
        if (n < 3) return 0.0;
        double len = std::hypot(coord[1].getx() - coord[0].getx(), coord[1].gety() - coord[0].gety());
        return len * len * std::tan(std::numbers::pi / n) / 4.0;
    }

    const std::unique_ptr<Point<T>[]>& getcoord() const { return coord; }
    std::size_t size() const noexcept { return n; }

    void setcoord(std::unique_ptr<Point<T>[]>&& p, std::size_t new_n) {
        coord = std::move(p);
        n = new_n;
    }
};