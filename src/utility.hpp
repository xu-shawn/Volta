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
   public:
    using array_type             = std::array<T, N>;
    using value_type             = T;
    using size_type              = typename array_type::size_type;
    using difference_type        = typename array_type::difference_type;
    using reference              = typename array_type::reference;
    using const_reference        = typename array_type::const_reference;
    using pointer                = typename array_type::pointer;
    using const_pointer          = typename array_type::const_pointer;
    using iterator               = typename array_type::iterator;
    using const_iterator         = typename array_type::const_iterator;
    using reverse_iterator       = typename array_type::reverse_iterator;
    using const_reverse_iterator = typename array_type::const_reverse_iterator;

    fixed_vector() :
        size_{0} {}

    constexpr fixed_vector(std::initializer_list<T> init_list) :
        data_{init_list},
        size_{init_list.size()} {}

    constexpr void push_back(const T& ele) {
        assert(size_ < N);
        data_[size_] = ele;
        size_++;
    }

    constexpr void push_back(T&& ele) {
        assert(size_ < N);
        data_[size_] = std::move(ele);
        size_++;
    }

    constexpr auto&       at(const std::size_t idx) { return data_.at(idx); }
    constexpr const auto& at(const std::size_t idx) const { return data_.at(idx); }

    constexpr auto& operator[](const std::size_t idx) noexcept {
        assert(idx < size_);
        return data_[idx];
    }

    constexpr const auto& operator[](const std::size_t idx) const noexcept {
        assert(idx < size_);
        return data_[idx];
    }

    constexpr auto&       front() noexcept { return data_.front(); }
    constexpr const auto& front() const noexcept { return data_.front(); }

    constexpr auto&       back() noexcept { return data_[size_ - 1]; }
    constexpr const auto& back() const noexcept { return data_[size_ - 1]; }

    constexpr auto*       data() noexcept { return data_.data(); }
    constexpr const auto* data() const noexcept { return data_.data(); }

    constexpr auto begin() noexcept { return data_.begin(); }
    constexpr auto begin() const noexcept { return data_.begin(); }
    constexpr auto cbegin() const noexcept { return data_.begin(); }

    constexpr auto end() noexcept { return std::next(data_.begin(), size_); }
    constexpr auto end() const noexcept { return std::next(data_.begin(), size_); }
    constexpr auto cend() const noexcept { return std::next(data_.begin(), size_); }

   private:
    array_type data_;
    size_type  size_;
};

template<typename T>
struct dependent_false: std::false_type {};

}

#endif
