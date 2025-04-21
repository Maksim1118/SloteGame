#pragma once

#include <random>
#include <type_traits>

namespace
{
    std::random_device rd;
    std::mt19937 gen(rd());
}

template<typename T>
T generateRandomValue(T minDist, T maxDist)
{
    static_assert(std::is_arithmetic<T>::value, "T must be an arithmetic type");
    if constexpr (std::is_integral<T>::value)
    {
        uniform_int_distribution<T> dis(minDist, maxDist);
        return dis(gen);
    }
    else
    {
        uniform_real_distribution<T> dis(minDist, maxDist);
        return dis(gen);
    }
}
