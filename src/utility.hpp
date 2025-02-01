#ifndef VOLTA_UTILITY_HPP__
#define VOLTA_UTILITY_HPP__

#include <cassert>
#include <cstdint>
#include <string_view>
#include <ranges>
#include <type_traits>
#include <vector>

namespace Volta::Utility {

template<typename T>
constexpr auto to_underlying(T value) {
    return static_cast<std::underlying_type_t<T>>(value);
}

constexpr auto split(std::string_view sv, char delimiter) {
    std::vector<std::string_view> result;

    std::size_t start = 0;
    std::size_t end   = sv.find(delimiter);

    while (end != std::string_view::npos)
    {
        result.emplace_back(sv.substr(start, end - start));
        start = end + 1;
        end   = sv.find(delimiter, start);
    }

    result.emplace_back(sv.substr(start));
    return result;
}

class PRNG {
   private:
    std::uint64_t s;

   public:
    constexpr PRNG(std::uint64_t seed) :
        s(seed) {
        if (s == 0)
            s = 1;
    }

    constexpr std::uint64_t rand() {
        s ^= s >> 12, s ^= s << 25, s ^= s >> 27;
        return s * 2685821657736338717LL;
    }

    constexpr std::uint64_t sparse_rand() { return rand() & rand() & rand(); }
};

template<typename T, std::size_t N>
class fixed_vector {
   private:
    std::array<T, N> data;
    std::size_t      size;

   public:
    constexpr fixed_vector() :
        size{0} {}
    constexpr void push_back(const T& ele) {
        assert(size < N);
        data[size] = ele;
        size++;
    }
    constexpr void push_back(T&& ele) {
        assert(size < N);
        data[size] = std::move(ele);
        size++;
    }
    constexpr T& operator[](const std::size_t idx) {
        assert(idx < size);
        return data[idx];
    }
    constexpr const T& operator[](const std::size_t idx) const {
        assert(idx < size);
        return data[idx];
    }
};

}

#endif
