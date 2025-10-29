#pragma once
#include <concepts>
#include <iostream>
#include <type_traits>
#include <cmath>
#include <memory>
#include "Figure.h"
#include "Point.h"
#include "Angle.h"
#include "Scalar.h"

template <class T, Scalar F>
class Array {
private:
    std::shared_ptr<T[]> figures{nullptr};
    size_t n{0};
public:
    Array() = default;
    Array(std::unique_ptr<T[]>&& f, size_t size): figures(std::shared_ptr<T[]>(std::move(f))), n(size) {}

    void remove(size_t index) {
        if (index >= n) return;
        auto p = std::shared_ptr<T[]>(new T[n - 1], std::default_delete<T[]>());
        size_t j = 0;
        for (size_t i = 0; i < n; ++i) {
            if (i == index) continue;
            p[j++] = figures[i];
        }
        figures = std::move(p);
        --n;
    }

    void print_centre() const {
        for (size_t i = 0; i < n; ++i) std::cout << figures[i].centre() << "\n";
    }

    void print_area() const {
        for (size_t i = 0; i < n; ++i) std::cout << static_cast<double>(figures[i]) << "\n";
    }

    double total_area() const {
        double sum = 0.0;
        for (size_t i = 0; i < n; ++i) sum += static_cast<double>(figures[i]);
        return sum;
    }
};
