#ifndef VOLTA_BITBOARD_HPP__
#define VOLTA_BITBOARD_HPP__

#include <algorithm>
#include <bit>
#include <bitset>
#include <cassert>
#include <cstdint>
#include <string>

#include "common.hpp"

namespace Volta::Chess {

class BitBoard {
   public:
    constexpr BitBoard() :
        bitboard_(0ULL) {}
    constexpr BitBoard(std::uint64_t bb) :
        bitboard_(bb) {}
    constexpr BitBoard(const BitBoard& other)            = default;
    constexpr BitBoard& operator=(const BitBoard& other) = default;

    [[nodiscard]] constexpr explicit operator std::uint64_t() const noexcept { return bitboard_; };
    [[nodiscard]] constexpr explicit operator bool() const noexcept { return bitboard_ != 0ULL; }
    [[nodiscard]] constexpr explicit operator std::string() const noexcept {
        std::string str_bitset = std::bitset<64>(bitboard_).to_string();

        std::string ret;
        for (int i = 0; i < 64; i += 8)
        {
            std::string x = str_bitset.substr(i, 8);
            std::reverse(x.begin(), x.end());
            ret += x + '\n';
        }

        return ret;
    }

    [[nodiscard]] constexpr bool empty() const noexcept { return bitboard_ == 0ULL; }

    [[nodiscard]] constexpr BitBoard operator|(const BitBoard& other) const noexcept {
        return BitBoard(bitboard_ | other.bitboard_);
    }

    [[nodiscard]] constexpr BitBoard operator&(const BitBoard& other) const noexcept {
        return BitBoard(bitboard_ & other.bitboard_);
    }

    [[nodiscard]] constexpr BitBoard operator^(const BitBoard& other) const noexcept {
        return BitBoard(bitboard_ ^ other.bitboard_);
    }

    [[nodiscard]] constexpr bool operator==(const BitBoard& other) const noexcept {
        return bitboard_ == other.bitboard_;
    }

    [[nodiscard]] constexpr bool operator!=(const BitBoard& other) const noexcept {
        return bitboard_ != other.bitboard_;
    }

    [[nodiscard]] constexpr BitBoard operator<<(const std::uint8_t shift) const noexcept {
        return bitboard_ << shift;
    }

    [[nodiscard]] constexpr BitBoard operator>>(const std::uint8_t shift) const noexcept {
        return bitboard_ >> shift;
    }

    template<Direction::underlying dir>
    [[nodiscard]] constexpr BitBoard shift() {
        if constexpr (dir == Direction::underlying::NORTH)
            return *this << 8;
        if constexpr (dir == Direction::underlying::SOUTH)
            return *this << 8;
        if constexpr (dir == Direction::underlying::NORTH)
            return *this << 8;
        if constexpr (dir == Direction::underlying::NORTH)
            return *this << 8;
    }

    constexpr BitBoard& operator|=(const BitBoard& other) noexcept {
        bitboard_ |= other.bitboard_;
        return *this;
    }

    constexpr BitBoard& operator&=(const BitBoard& other) noexcept {
        bitboard_ &= other.bitboard_;
        return *this;
    }

    constexpr BitBoard& operator^=(const BitBoard& other) noexcept {
        bitboard_ ^= other.bitboard_;
        return *this;
    }

    constexpr BitBoard& operator<<=(const std::uint8_t shift) noexcept {
        bitboard_ <<= shift;
        return *this;
    }

    constexpr BitBoard& operator>>=(const std::uint8_t shift) noexcept {
        bitboard_ >>= shift;
        return *this;
    }

    [[nodiscard]] constexpr int lsb() const noexcept { return std::countr_zero(bitboard_); }
    [[nodiscard]] constexpr int msb() const noexcept { return 64 - std::countl_zero(bitboard_); }
    [[nodiscard]] constexpr int popcount() const noexcept { return std::popcount(bitboard_); }

    constexpr void                       remove_lsb() noexcept { bitboard_ &= (bitboard_ - 1); }
    [[nodiscard]] constexpr std::uint8_t pop_lsb() noexcept {
        assert(!empty());
        int ret = lsb();
        remove_lsb();
        return ret;
    }

   private:
    std::uint64_t bitboard_;
};

}

#endif
