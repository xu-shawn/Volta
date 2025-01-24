#ifndef VOLTA_UTILITY_HPP__
#define VOLTA_UTILITY_HPP__

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

}

#endif
