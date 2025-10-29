#include <gtest/gtest.h>
#include <cmath>
#include <memory>
#include "Point.h"
#include "Figure.h"
#include "Angle.h"
#include "Array.h"

template<typename T>
std::unique_ptr<Point<T>[]> make_regular_polygon(std::size_t n, T radius) {
    auto p = std::make_unique<Point<T>[]>(n);
    for (std::size_t i = 0; i < n; ++i) {
        double angle = 2.0 * M_PI * i / static_cast<double>(n);
        p[i] = Point<T>(radius * std::cos(angle), radius * std::sin(angle));
    }
    return p;
}

TEST(PointTest, EqualityAndAccessors) {
    Point<double> p1(1.0, 2.0), p2(1.0, 2.0);
    EXPECT_TRUE(p1 == p2);
    p1.setx(3.0);
    EXPECT_DOUBLE_EQ(p1.getx(), 3.0);
    EXPECT_TRUE(p1 != p2);
}

TEST(FigureTest, CentreCalculation) {
    constexpr std::size_t n = 4;
    constexpr double radius = 2.0;
    auto pts = make_regular_polygon<double>(n, radius);
    Figure<double> f(std::move(pts), n);
    auto c = f.centre();
    EXPECT_NEAR(c.getx(), 0.0, 1e-9);
    EXPECT_NEAR(c.gety(), 0.0, 1e-9);
}

TEST(FigureTest, CopyAndCompare) {
    constexpr std::size_t n = 5;
    constexpr int radius = 3;
    auto p = make_regular_polygon<int>(n, radius);
    Figure<int> f1(std::move(p), n);
    Figure<int> f2 = f1;
    EXPECT_TRUE(f1 == f2);
    Figure<int> f3;
    f3 = f1;
    EXPECT_TRUE(f3 == f1);
}

TEST(TriangleTest, AreaFromSide) {
    constexpr double radius = 1.0;
    auto pts = make_regular_polygon<double>(3, radius);
    Triangle<double> t(std::move(pts));
    double len = std::hypot(std::cos(2*M_PI/3) - 1.0, std::sin(2*M_PI/3));
    double expected = (std::sqrt(3.0) / 4.0) * len * len;
    EXPECT_NEAR(static_cast<double>(t), expected, 1e-9);
}

TEST(FourangleTest, AreaFromSide) {
    constexpr double radius = 1.0;
    auto pts = make_regular_polygon<double>(4, radius);
    Fourangle<double> f(std::move(pts));
    double len = std::hypot(std::cos(M_PI/2) - 1.0, std::sin(M_PI/2));
    double expected = len * len;
    EXPECT_NEAR(static_cast<double>(f), expected, 1e-9);
}

TEST(EightangleTest, AreaFromSide) {
    constexpr double radius = 1.0;
    auto pts = make_regular_polygon<double>(8, radius);
    Eightangle<double> e(std::move(pts));
    double len = std::hypot(std::cos(M_PI/4) - 1.0, std::sin(M_PI/4));
    double expected = 2.0 * len * len * (std::sqrt(2.0) + 1.0);
    EXPECT_NEAR(static_cast<double>(e), expected, 1e-9);
}

TEST(ArrayTest, TotalAreaAndRemove) {
    constexpr std::size_t count = 3;
    constexpr double base_radius = 1.0;
    auto figs = std::make_unique<Fourangle<double>[]>(count);
    for (std::size_t i = 0; i < count; ++i)
        figs[i] = Fourangle<double>(make_regular_polygon<double>(4, base_radius + i * 0.5));
    Array<Fourangle<double>, double> arr(std::move(figs), count);
    double expected_total = 0.0;
    for (std::size_t i = 0; i < count; ++i) {
        double len = std::hypot(std::cos(M_PI/2) - 1.0, std::sin(M_PI/2)) * (base_radius + i * 0.5);
        expected_total += len * len;
    }
    EXPECT_NEAR(arr.total_area(), expected_total, 1e-9);
    arr.remove(1);
    double removed_len = std::hypot(std::cos(M_PI/2) - 1.0, std::sin(M_PI/2)) * (base_radius + 0.5);
    double expected_after = expected_total - removed_len * removed_len;
    EXPECT_NEAR(arr.total_area(), expected_after, 1e-9);
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}