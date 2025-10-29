#include <iostream>
#include <memory>
#include <cmath>
#include "Point.h"
#include "Figure.h"
#include "Angle.h"
#include "Array.h"

template <typename T>
std::unique_ptr<Point<T>[]> make_regular_polygon(std::size_t n, T radius) {
    auto p = std::make_unique<Point<T>[]>(n);
    for (std::size_t i = 0; i < n; ++i) {
        double angle = 2.0 * M_PI * static_cast<double>(i) / static_cast<double>(n);
        p[i] = Point<T>(static_cast<T>(radius * std::cos(angle)),
                        static_cast<T>(radius * std::sin(angle)));
    }
    return p;
}

int main() {
    Point<int> p1(1, 2);
    Point<int> p2(1, 2);
    std::cout << "Point<int> == : " << (p1 == p2) << "\n";
    p1.setx(3);
    std::cout << "Point<int> != : " << (p1 != p2) << "\n";
    std::cout << "GetX: " << p1.getx() << " GetY: " << p1.gety() << "\n";

    auto pts4_int = make_regular_polygon<int>(4, 2);
    Figure<int> f_int(std::move(pts4_int), 4);
    auto c_int = f_int.centre();
    std::cout << "Figure<int> centre: " << c_int << "\n";

    auto pts3_int = make_regular_polygon<int>(3, 1);
    Triangle<int> t_int(std::move(pts3_int));
    std::cout << "Triangle<int> area: " << static_cast<double>(t_int) << "\n";

    auto ptsq_int = make_regular_polygon<int>(4, 1);
    Fourangle<int> q_int(std::move(ptsq_int));
    std::cout << "Fourangle<int> area: " << static_cast<double>(q_int) << "\n";

    auto ptso_int = make_regular_polygon<int>(8, 1);
    Eightangle<int> o_int(std::move(ptso_int));
    std::cout << "Eightangle<int> area: " << static_cast<double>(o_int) << "\n";

    const std::size_t count_int = 3;
    auto figs_int = std::make_unique<Fourangle<int>[]>(count_int);
    for (std::size_t i = 0; i < count_int; ++i) {
        figs_int[i] = Fourangle<int>(make_regular_polygon<int>(4, 1 + i * 0.5));
    }
    Array<Fourangle<int>, double> arr_int(std::move(figs_int), count_int);
    std::cout << "Centres<int>:\n";
    arr_int.print_centre();
    std::cout << "Areas<int>:\n";
    arr_int.print_area();
    std::cout << "Total area<int>: " << arr_int.total_area() << "\n";
    arr_int.remove(1);
    std::cout << "After remove total area<int>: " << arr_int.total_area() << "\n";

    Point<double> pd1(1.0, 2.0);
    Point<double> pd2(1.0, 2.0);
    std::cout << "Point<double> == : " << (pd1 == pd2) << "\n";
    pd1.setx(3.0);
    std::cout << "Point<double> != : " << (pd1 != pd2) << "\n";
    std::cout << "GetX: " << pd1.getx() << " GetY: " << pd1.gety() << "\n";

    auto pts4_double = make_regular_polygon<double>(4, 2.0);
    Figure<double> f_double(std::move(pts4_double), 4);
    auto c_double = f_double.centre();
    std::cout << "Figure<double> centre: " << c_double << "\n";

    auto pts3_double = make_regular_polygon<double>(3, 1.0);
    Triangle<double> t_double(std::move(pts3_double));
    std::cout << "Triangle<double> area: " << static_cast<double>(t_double) << "\n";

    auto ptsq_double = make_regular_polygon<double>(4, 1.0);
    Fourangle<double> q_double(std::move(ptsq_double));
    std::cout << "Fourangle<double> area: " << static_cast<double>(q_double) << "\n";

    auto ptso_double = make_regular_polygon<double>(8, 1.0);
    Eightangle<double> o_double(std::move(ptso_double));
    std::cout << "Eightangle<double> area: " << static_cast<double>(o_double) << "\n";

    const std::size_t count_double = 3;
    auto figs_double = std::make_unique<Fourangle<double>[]>(count_double);
    for (std::size_t i = 0; i < count_double; ++i) {
        figs_double[i] = Fourangle<double>(make_regular_polygon<double>(4, 1.0 + i * 0.5));
    }
    Array<Fourangle<double>, double> arr_double(std::move(figs_double), count_double);
    std::cout << "Centres<double>:\n";
    arr_double.print_centre();
    std::cout << "Areas<double>:\n";
    arr_double.print_area();
    std::cout << "Total area<double>: " << arr_double.total_area() << "\n";
    arr_double.remove(1);
    std::cout << "After remove total area<double>: " << arr_double.total_area() << "\n";

    return 0;
}