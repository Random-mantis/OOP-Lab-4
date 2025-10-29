#include <iostream>
#include <memory>
#include <cmath>
#include "Point.h"
#include "Figure.h"
#include "Angle.h"
#include "Array.h"

template <class T>
std::unique_ptr<Point<T>[]> make_regular_polygon(std::size_t n, T radius) {
    auto p = std::make_unique<Point<T>[]>(n);
    for (std::size_t i = 0; i < n; ++i) {
        double angle = 2.0 * M_PI * static_cast<double>(i) / static_cast<double>(n);
        p[i] = Point<T>(radius * std::cos(angle), radius * std::sin(angle));
    }
    return p;
}

int main() {
    Point<double> p1(1.0, 2.0);
    Point<double> p2(1.0, 2.0);
    std::cout << "Point == : " << (p1 == p2) << "\n";
    p1.setx(3.0);
    std::cout << "Point != : " << (p1 != p2) << "\n";
    std::cout << "GetX: " << p1.getx() << " GetY: " << p1.gety() << "\n";

    {
        auto pts4 = make_regular_polygon<double>(4, 2.0);
        Figure<double> f(std::move(pts4), 4);
        auto c = f.centre();
        std::cout << "Figure centre: " << c << "\n";
    }

    {
        auto pts3 = make_regular_polygon<double>(3, 1.0);
        Triangle<double> t(std::move(pts3));
        std::cout << "Triangle area: " << static_cast<double>(t) << "\n";
    }

    {
        auto ptsq = make_regular_polygon<double>(4, 1.0);
        Fourangle<double> q(std::move(ptsq));
        std::cout << "Fourangle area: " << static_cast<double>(q) << "\n";
    }

    {
        auto ptso = make_regular_polygon<double>(8, 1.0);
        Eightangle<double> o(std::move(ptso));
        std::cout << "Eightangle area: " << static_cast<double>(o) << "\n";
    }

    {
        const std::size_t count = 3;
        auto figs = std::make_unique<Fourangle<double>[]>(count);
        for (std::size_t i = 0; i < count; ++i) {
            figs[i] = Fourangle<double>(make_regular_polygon<double>(4, 1.0 + i * 0.5));
        }

        Array<Fourangle<double>, double> arr(std::move(figs), count);
        std::cout << "Centres:\n";
        arr.print_centre();
        std::cout << "Areas:\n";
        arr.print_area();
        std::cout << "Total area: " << arr.total_area() << "\n";
        arr.remove(1);
        std::cout << "After remove total area: " << arr.total_area() << "\n";
    }

    return 0;
}