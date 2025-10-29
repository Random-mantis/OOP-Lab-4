#pragma once
#include <iostream>

template <typename T>
concept Scalar = std::is_scalar_v<T>;