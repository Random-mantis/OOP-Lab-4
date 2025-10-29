#pragma once
#include <concepts>
#include <iostream>
#include <type_traits>
#include <cmath>
#include <memory>
#include "Figure.h"
#include "Point.h"
#include "Scalar.h"

template<Scalar T>
class Triangle : public Figure<T> {
public:
    Triangle() : Figure<T>(3) {}
    Triangle(std::unique_ptr<Point<T>[]>&& p) : Figure<T>(std::move(p), 3) {}
    Triangle(const Triangle& other) : Figure<T>(other) {}
    ~Triangle() = default;

    Triangle& operator=(const Triangle& other) {
        Figure<T>::operator=(other);
        return *this;
    }

    operator double() const override {
        auto& coord = this->getcoord();
        double len = std::hypot(coord[1].getx() - coord[0].getx(), coord[1].gety() - coord[0].gety());
        return (std::sqrt(3.0) / 4.0) * len * len;
    }
};

template<Scalar T>
class Fourangle : public Figure<T> {
public:
    Fourangle() : Figure<T>(4) {}
    Fourangle(std::unique_ptr<Point<T>[]>&& p) : Figure<T>(std::move(p), 4) {}
    Fourangle(const Fourangle& other) : Figure<T>(other) {}
    ~Fourangle() = default;

    Fourangle& operator=(const Fourangle& other) {
        Figure<T>::operator=(other);
        return *this;
    }

    operator double() const override {
        auto& coord = this->getcoord();
        double len = std::hypot(coord[1].getx() - coord[0].getx(), coord[1].gety() - coord[0].gety());
        return len * len;
    }
};

template<Scalar T>
class Eightangle : public Figure<T> {
public:
    Eightangle() : Figure<T>(8) {}
    Eightangle(std::unique_ptr<Point<T>[]>&& p) : Figure<T>(std::move(p), 8) {}
    Eightangle(const Eightangle& other) : Figure<T>(other) {}
    ~Eightangle() = default;

    Eightangle& operator=(const Eightangle& other) {
        Figure<T>::operator=(other);
        return *this;
    }

    operator double() const override {
        auto& coord = this->getcoord();
        double len = std::hypot(coord[1].getx() - coord[0].getx(), coord[1].gety() - coord[0].gety());
        return 2.0 * len * len * (std::sqrt(2.0) + 1.0);
    }
};