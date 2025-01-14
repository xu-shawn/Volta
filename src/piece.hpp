#ifndef VOLTA_PIECE_HPP__
#define VOLTA_PIECE_HPP__

#include <cstdint>
#include <type_traits>

#include "utility.hpp"

namespace Volta::Chess {

class PieceType {
   private:
    enum class underlying : std::uint8_t {
        PAWN = 0,
        KNIGHT,
        BISHOP,
        ROOK,
        QUEEN,
        KING,
        NONE
    };

    constexpr PieceType(underlying pt) :
        piece_type{pt} {}

    underlying piece_type;

   public:
    using underlying_type_t = std::underlying_type_t<underlying>;

    constexpr PieceType() :
        piece_type(underlying::NONE) {}

    constexpr auto to_underlying() const noexcept { return Utility::to_underlying(piece_type); }

    static constexpr PieceType   PAWN() noexcept { return underlying::PAWN; }
    static constexpr PieceType   KNIGHT() noexcept { return underlying::KNIGHT; }
    static constexpr PieceType   BISHOP() noexcept { return underlying::BISHOP; }
    static constexpr PieceType   ROOK() noexcept { return underlying::ROOK; }
    static constexpr PieceType   QUEEN() noexcept { return underlying::QUEEN; }
    static constexpr PieceType   NONE() noexcept { return underlying::NONE; }
    static constexpr std::size_t COUNT() noexcept { return 6; }

    static constexpr PieceType from_ordinal(auto ordinal) noexcept {
        return static_cast<underlying>(ordinal);
    }
};


}

#endif
