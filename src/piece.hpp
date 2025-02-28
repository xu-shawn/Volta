#ifndef VOLTA_PIECE_HPP__
#define VOLTA_PIECE_HPP__

#include <cassert>
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
    static constexpr PieceType   KING() noexcept { return underlying::KING; }
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

    static constexpr Piece from_char(char ch) noexcept {
        switch (ch)
        {
        case 'p' :
            return Piece::WHITE_PAWN();
        case 'n' :
            return Piece::WHITE_KNIGHT();
        case 'b' :
            return Piece::WHITE_BISHOP();
        case 'r' :
            return Piece::WHITE_ROOK();
        case 'q' :
            return Piece::WHITE_QUEEN();
        case 'k' :
            return Piece::WHITE_KING();
        case 'P' :
            return Piece::BLACK_PAWN();
        case 'N' :
            return Piece::BLACK_KNIGHT();
        case 'B' :
            return Piece::BLACK_BISHOP();
        case 'R' :
            return Piece::BLACK_ROOK();
        case 'Q' :
            return Piece::BLACK_QUEEN();
        case 'K' :
            return Piece::BLACK_KING();
        }

        return Piece::NONE();
    }

    constexpr char to_char() const noexcept {
        switch (piece)
        {
        case underlying::WHITE_PAWN :
            return 'p';
        case underlying::WHITE_KNIGHT :
            return 'n';
        case underlying::WHITE_BISHOP :
            return 'b';
        case underlying::WHITE_ROOK :
            return 'r';
        case underlying::WHITE_QUEEN :
            return 'q';
        case underlying::WHITE_KING :
            return 'k';
        case underlying::BLACK_PAWN :
            return 'P';
        case underlying::BLACK_KNIGHT :
            return 'N';
        case underlying::BLACK_BISHOP :
            return 'B';
        case underlying::BLACK_ROOK :
            return 'R';
        case underlying::BLACK_QUEEN :
            return 'Q';
        case underlying::BLACK_KING :
            return 'K';
        case underlying::NONE :
            return ' ';
        }

        return '0';
    }

    static constexpr Piece WHITE_PAWN() noexcept { return underlying::WHITE_PAWN; }
    static constexpr Piece WHITE_KNIGHT() noexcept { return underlying::WHITE_KNIGHT; }
    static constexpr Piece WHITE_BISHOP() noexcept { return underlying::WHITE_BISHOP; }
    static constexpr Piece WHITE_ROOK() noexcept { return underlying::WHITE_ROOK; }
    static constexpr Piece WHITE_QUEEN() noexcept { return underlying::WHITE_QUEEN; }
    static constexpr Piece WHITE_KING() noexcept { return underlying::WHITE_KING; }

    static constexpr Piece BLACK_PAWN() noexcept { return underlying::BLACK_PAWN; }
    static constexpr Piece BLACK_KNIGHT() noexcept { return underlying::BLACK_KNIGHT; }
    static constexpr Piece BLACK_BISHOP() noexcept { return underlying::BLACK_BISHOP; }
    static constexpr Piece BLACK_ROOK() noexcept { return underlying::BLACK_ROOK; }
    static constexpr Piece BLACK_QUEEN() noexcept { return underlying::BLACK_QUEEN; }
    static constexpr Piece BLACK_KING() noexcept { return underlying::BLACK_KING; }

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
