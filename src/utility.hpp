#ifndef VOLTA_UTILITY_HPP__
#define VOLTA_UTILITY_HPP__

#include <type_traits>

namespace Volta::Utility {

template<typename T>
constexpr auto to_underlying(T value) {
    return static_cast<std::underlying_type_t<T>>(value);
}

}

#endif
