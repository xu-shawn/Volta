#ifndef VOLTA_COORDINATES_HPP__
#define VOLTA_COORDINATES_HPP__

#include <cstdint>
#include <type_traits>

#include "bitboard.hpp"
#include "utility.hpp"

namespace Volta::Chess {

class File {
   private:
    enum class underlying : std::uint8_t {
        FILE_A = 0,
        FILE_B,
        FILE_C,
        FILE_D,
        FILE_E,
        FILE_F,
        FILE_G,
        FILE_H
    };

    underlying file;

    constexpr File(const underlying file) :
        file{file} {}

    static constexpr BitBoard FILE_A_BB = 0x0101010101010101;

   public:
    using underlying_type_t = std::underlying_type_t<underlying>;

    static_assert(std::is_same_v<decltype(Utility::to_underlying(file)), underlying_type_t>);

    constexpr auto to_underlying() const noexcept { return Utility::to_underlying(file); }

    static constexpr File FILE_A() noexcept { return underlying::FILE_A; }
    static constexpr File FILE_B() noexcept { return underlying::FILE_B; }
    static constexpr File FILE_C() noexcept { return underlying::FILE_C; }
    static constexpr File FILE_D() noexcept { return underlying::FILE_D; }
    static constexpr File FILE_E() noexcept { return underlying::FILE_E; }
    static constexpr File FILE_F() noexcept { return underlying::FILE_F; }
    static constexpr File FILE_G() noexcept { return underlying::FILE_G; }
    static constexpr File FILE_H() noexcept { return underlying::FILE_H; }

    constexpr BitBoard to_bb() { return FILE_A_BB << to_underlying(); }
    constexpr          operator BitBoard() { return to_bb(); }
};

class Rank {
   private:
    enum class underlying : std::uint8_t {
        RANK_1 = 0,
        RANK_2,
        RANK_3,
        RANK_4,
        RANK_5,
        RANK_6,
        RANK_7,
        RANK_8
    };

    underlying rank;

    constexpr Rank(const underlying rank) :
        rank{rank} {}

    static constexpr BitBoard RANK_1_BB = 0x0000000000000ff;

   public:
    using underlying_type_t = std::underlying_type_t<underlying>;

    static_assert(std::is_same_v<decltype(Utility::to_underlying(rank)), underlying_type_t>);

    constexpr auto to_underlying() const noexcept { return Utility::to_underlying(rank); }

    static constexpr Rank RANK_1() noexcept { return underlying::RANK_1; }
    static constexpr Rank RANK_2() noexcept { return underlying::RANK_2; }
    static constexpr Rank RANK_3() noexcept { return underlying::RANK_3; }
    static constexpr Rank RANK_4() noexcept { return underlying::RANK_4; }
    static constexpr Rank RANK_5() noexcept { return underlying::RANK_5; }
    static constexpr Rank RANK_6() noexcept { return underlying::RANK_6; }
    static constexpr Rank RANK_7() noexcept { return underlying::RANK_7; }
    static constexpr Rank RANK_8() noexcept { return underlying::RANK_8; }

    constexpr BitBoard to_bb() { return RANK_1_BB << (8 * to_underlying()); }
    constexpr          operator BitBoard() { return to_bb(); }
};

class Square {
   private:
    enum class underlying : std::uint8_t {
    };
};

}

#endif
