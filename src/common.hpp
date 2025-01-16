#ifndef VOLTA_COMMON_HPP__
#define VOLTA_COMMON_HPP__

#include <cstdint>
#include <type_traits>

#include "utility.hpp"

namespace Volta::Chess {

class BitBoard;

class Direction {
   private:
    enum class underlying : std::int8_t {
        NORTH = 8,
        EAST  = 1,
        SOUTH = -NORTH,
        WEST  = -EAST,

        NORTH_EAST = NORTH + EAST,
        SOUTH_EAST = SOUTH + EAST,
        SOUTH_WEST = SOUTH + WEST,
        NORTH_WEST = NORTH + WEST
    };

    underlying direction;

    constexpr Direction(const underlying dir) :
        direction{dir} {}

    using underlying_type_t = std::underlying_type_t<underlying>;

    static_assert(std::is_same_v<decltype(Utility::to_underlying(direction)), underlying_type_t>);

   public:
    constexpr auto to_underlying() { return Utility::to_underlying(direction); }

    constexpr operator underlying() { return direction; }

    static constexpr Direction NORTH() { return underlying::NORTH; }
    static constexpr Direction SOUTH() { return underlying::SOUTH; }
    static constexpr Direction EAST() { return underlying::EAST; }
    static constexpr Direction WEST() { return underlying::WEST; }

    static constexpr Direction NORTH_EAST() { return underlying::NORTH_EAST; }
    static constexpr Direction NORTH_WEST() { return underlying::NORTH_WEST; }
    static constexpr Direction SOUTH_EAST() { return underlying::SOUTH_EAST; }
    static constexpr Direction SOUTH_WEST() { return underlying::SOUTH_WEST; }

    template<Direction::underlying dir>
    friend constexpr BitBoard shift(BitBoard bb);
};

class Color {
   private:
    enum class underlying : std::uint8_t {
        WHITE,
        BLACK
    };

    constexpr Color(underlying c) :
        color{c} {}

    underlying color;

   public:
    using underlying_type_t = std::underlying_type_t<underlying>;

    constexpr auto to_underlying() const noexcept { return Utility::to_underlying(color); }

    static constexpr Color from_ordinal(auto ordinal) noexcept {
        return static_cast<underlying>(ordinal);
    }

    static constexpr Color       WHITE() noexcept { return underlying::WHITE; }
    static constexpr Color       BLACK() noexcept { return underlying::BLACK; }
    static constexpr std::size_t COUNT() noexcept { return 2; }
};
}

#endif
