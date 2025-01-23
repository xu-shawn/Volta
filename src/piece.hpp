#ifndef VOLTA_PIECE_HPP__
#define VOLTA_PIECE_HPP__

#include <cstdint>

#include "common.hpp"
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
        piece_type{underlying::NONE} {}

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

    constexpr bool operator==(const PieceType& other) const noexcept {
        return piece_type == other.piece_type;
    }
};

class Piece {
   private:
    enum class underlying : std::uint8_t {
        WHITE_PAWN,
        WHITE_KNIGHT,
        WHITE_BISHOP,
        WHITE_ROOK,
        WHITE_QUEEN,
        WHITE_KING,

        BLACK_PAWN,
        BLACK_KNIGHT,
        BLACK_BISHOP,
        BLACK_ROOK,
        BLACK_QUEEN,
        BLACK_KING,

        NONE
    };

    constexpr Piece(underlying p) :
        piece{p} {}

    underlying piece;

   public:
    using underlying_type_t = std::underlying_type_t<underlying>;

    constexpr Piece() :
        piece{underlying::NONE} {}

    constexpr auto to_underlying() const noexcept { return Utility::to_underlying(piece); }

    static constexpr Piece make(PieceType type, Color color) noexcept {
        return static_cast<underlying>(color.to_underlying() * Piece::COUNT()
                                       + type.to_underlying());
    }

    static constexpr Piece from_ordinal(auto ordinal) noexcept {
        return static_cast<underlying>(ordinal);
    }

    static constexpr Piece WHITE_PAWN() noexcept { return underlying::WHITE_PAWN; }
    static constexpr Piece WHITE_KNIGHT() noexcept { return underlying::WHITE_KNIGHT; }
    static constexpr Piece WHITE_BISHOP() noexcept { return underlying::WHITE_BISHOP; }
    static constexpr Piece WHITE_ROOK() noexcept { return underlying::WHITE_ROOK; }
    static constexpr Piece WHITE_QUEEN() noexcept { return underlying::WHITE_QUEEN; }

    static constexpr Piece BLACK_PAWN() noexcept { return underlying::BLACK_PAWN; }
    static constexpr Piece BLACK_KNIGHT() noexcept { return underlying::BLACK_KNIGHT; }
    static constexpr Piece BLACK_BISHOP() noexcept { return underlying::BLACK_BISHOP; }
    static constexpr Piece BLACK_ROOK() noexcept { return underlying::BLACK_ROOK; }
    static constexpr Piece BLACK_QUEEN() noexcept { return underlying::BLACK_QUEEN; }

    static constexpr Piece       NONE() noexcept { return underlying::NONE; }
    static constexpr std::size_t COUNT() noexcept { return 6; }

    constexpr bool is_valid() const noexcept { return piece != underlying::NONE; }

    constexpr Color color() const noexcept { return Color::from_ordinal(to_underlying() >= 6); }

    constexpr PieceType type() const noexcept {
        return PieceType::from_ordinal(to_underlying() > 5 ? to_underlying() - 6 : to_underlying());
    }

    constexpr bool operator==(const Piece& other) const noexcept { return piece == other.piece; }
};

}

#endif
