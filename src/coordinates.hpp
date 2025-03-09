#ifndef VOLTA_COORDINATES_HPP__
#define VOLTA_COORDINATES_HPP__

#include <cassert>
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

    constexpr File(const underlying_type_t ordinal) :
        file{ordinal} {}

    static constexpr File from_ordinal(auto ordinal) {
        assert(ordinal >= 0);
        assert(ordinal < 8);
        return File{static_cast<underlying_type_t>(ordinal)};
    }

    static constexpr File from_char(char ch) {
        assert(ch >= 'a');
        assert(ch <= 'h');
        return from_ordinal(ch - 'a');
    }

    static constexpr File FILE_A() noexcept { return underlying::FILE_A; }
    static constexpr File FILE_B() noexcept { return underlying::FILE_B; }
    static constexpr File FILE_C() noexcept { return underlying::FILE_C; }
    static constexpr File FILE_D() noexcept { return underlying::FILE_D; }
    static constexpr File FILE_E() noexcept { return underlying::FILE_E; }
    static constexpr File FILE_F() noexcept { return underlying::FILE_F; }
    static constexpr File FILE_G() noexcept { return underlying::FILE_G; }
    static constexpr File FILE_H() noexcept { return underlying::FILE_H; }

    static constexpr std::size_t COUNT() noexcept { return 8; }

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

    constexpr Rank(const underlying_type_t ordinal) :
        rank{ordinal} {}

    static constexpr Rank from_ordinal(auto ordinal) {
        assert(ordinal >= 0);
        assert(ordinal < 8);
        return Rank{static_cast<underlying_type_t>(ordinal)};
    }

    static constexpr Rank from_char(char ch) {
        assert(ch >= '1');
        assert(ch <= '8');
        return from_ordinal(ch - '1');
    }

    static constexpr Rank RANK_1() noexcept { return underlying::RANK_1; }
    static constexpr Rank RANK_2() noexcept { return underlying::RANK_2; }
    static constexpr Rank RANK_3() noexcept { return underlying::RANK_3; }
    static constexpr Rank RANK_4() noexcept { return underlying::RANK_4; }
    static constexpr Rank RANK_5() noexcept { return underlying::RANK_5; }
    static constexpr Rank RANK_6() noexcept { return underlying::RANK_6; }
    static constexpr Rank RANK_7() noexcept { return underlying::RANK_7; }
    static constexpr Rank RANK_8() noexcept { return underlying::RANK_8; }

    static constexpr std::size_t COUNT() noexcept { return 8; }

    constexpr BitBoard to_bb() { return RANK_1_BB << (8 * to_underlying()); }
    constexpr          operator BitBoard() { return to_bb(); }
};

class Square {
   private:
    // clang-format off
    enum class underlying : std::uint8_t {
        A1 = 0, B1, C1, D1, E1, F1, G1, H1,
        A2, B2, C2, D2, E2, F2, G2, H2,
        A3, B3, C3, D3, E3, F3, G3, H3,
        A4, B4, C4, D4, E4, F4, G4, H4,
        A5, B5, C5, D5, E5, F5, G5, H5,
        A6, B6, C6, D6, E6, F6, G6, H6,
        A7, B7, C7, D7, E7, F7, G7, H7,
        A8, B8, C8, D8, E8, F8, G8, H8,
        None,
    };
    // clang-format on

    underlying square;

    constexpr Square(underlying sq) noexcept :
        square{sq} {}

   public:
    using underlying_type_t = std::underlying_type_t<underlying>;

    static_assert(std::is_same_v<decltype(Utility::to_underlying(square)), underlying_type_t>);

    constexpr auto to_underlying() const noexcept { return Utility::to_underlying(square); }
    constexpr auto ordinal() const noexcept { return to_underlying(); }
    constexpr      operator std::string() const noexcept {
        auto square = std::string();
        square.push_back('a' + file().to_underlying());
        square.push_back('1' + rank().to_underlying());
        return square;
    }

    constexpr Square() noexcept :
        square{underlying::None} {}

    constexpr Square(File f, Rank r) noexcept :
        square{static_cast<underlying_type_t>(f.to_underlying() + r.to_underlying() * 8)} {}

    constexpr File     file() const noexcept { return File::from_ordinal(ordinal() % 8); }
    constexpr Rank     rank() const noexcept { return Rank::from_ordinal(ordinal() / 8); }
    constexpr BitBoard to_bb() const noexcept { return 1ULL << ordinal(); }
    constexpr bool     is_valid() const noexcept { return square != underlying::None; }

    static constexpr Square NONE() noexcept { return underlying::None; }

    static constexpr std::size_t COUNT() noexcept { return 64; }

    static constexpr Square from_ordinal(auto ordinal) noexcept {
        return static_cast<underlying>(ordinal);
    }

    static constexpr Square from_string(std::string_view str) noexcept {
        if (str.length() != 2)
            return NONE();

        return Square(File::from_char(str[0]), Rank::from_char(str[1]));
    }
};

inline auto constexpr distance(File f1, File f2) {
    return std::abs(f1.to_underlying() - f2.to_underlying());
}

inline auto constexpr distance(Rank r1, Rank r2) {
    return std::abs(r1.to_underlying() - r2.to_underlying());
}

inline auto constexpr distance(Square s1, Square s2) {
    return distance(s1.file(), s2.file()) + distance(s1.rank(), s2.rank());
}

}

#endif
