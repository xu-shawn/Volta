#ifndef VOLTA_MOVE_HPP__
#define VOLTA_MOVE_HPP__

#include <cstdint>
#include <type_traits>

#include "coordinates.hpp"
#include "piece.hpp"
#include "utility.hpp"

namespace Volta::Chess {


class MoveFlag {
   private:
    enum class underlying : std::uint8_t {
        NORMAL                   = 0b0000,
        CAPTURE                  = 0b0001,
        EN_PASSANT               = 0b0010,
        PROMOTION                = 0b0100,
        KNIGHT_PROMOTION         = 0b0100 & (PieceType::KNIGHT().to_underlying() - 1),
        BISHOP_PROMOTION         = 0b0100 & (PieceType::BISHOP().to_underlying() - 1),
        ROOK_PROMOTION           = 0b0100 & (PieceType::ROOK().to_underlying() - 1),
        QUEEN_PROMOTION          = 0b0100 & (PieceType::QUEEN().to_underlying() - 1),
        PROMOTION_CAPTURE        = 0b1100,
        KNIGHT_PROMOTION_CAPTURE = 0b1100 & (PieceType::KNIGHT().to_underlying() - 1),
        BISHOP_PROMOTION_CAPTURE = 0b1100 & (PieceType::BISHOP().to_underlying() - 1),
        ROOK_PROMOTION_CAPTURE   = 0b1100 & (PieceType::ROOK().to_underlying() - 1),
        QUEEN_PROMOTION_CAPTURE  = 0b1100 & (PieceType::QUEEN().to_underlying() - 1),
    };

    constexpr MoveFlag(underlying f) :
        move_flag{f} {}

    underlying move_flag;

   public:
    using underlying_type_t = std::underlying_type_t<underlying>;

    constexpr auto to_underlying() { return Utility::to_underlying(move_flag); }

    static constexpr MoveFlag NORMAL() { return underlying::NORMAL; }
    static constexpr MoveFlag CAPTURE() { return underlying::CAPTURE; }
    static constexpr MoveFlag EN_PASSANT() { return underlying::EN_PASSANT; }
    static constexpr MoveFlag PROMOTION() { return underlying::PROMOTION; }
    static constexpr MoveFlag KNIGHT_PROMOTION() { return underlying::KNIGHT_PROMOTION; }
    static constexpr MoveFlag BISHOP_PROMOTION() { return underlying::BISHOP_PROMOTION; }
    static constexpr MoveFlag ROOK_PROMOTION() { return underlying::ROOK_PROMOTION; }
    static constexpr MoveFlag QUEEN_PROMOTION() { return underlying::QUEEN_PROMOTION; }
    static constexpr MoveFlag KNIGHT_PROMOTION_CAPTURE() {
        return underlying::KNIGHT_PROMOTION_CAPTURE;
    }
    static constexpr MoveFlag BISHOP_PROMOTION_CAPTURE() {
        return underlying::BISHOP_PROMOTION_CAPTURE;
    }
    static constexpr MoveFlag ROOK_PROMOTION_CAPTURE() {
        return underlying::ROOK_PROMOTION_CAPTURE;
    }
    static constexpr MoveFlag QUEEN_PROMOTION_CAPTURE() {
        return underlying::QUEEN_PROMOTION_CAPTURE;
    }

    constexpr bool is_capture() const noexcept {
        return (Utility::to_underlying(move_flag) & Utility::to_underlying(underlying::CAPTURE))
            == Utility::to_underlying(underlying::CAPTURE);
    }

    constexpr bool is_promotion() const noexcept {
        return (Utility::to_underlying(move_flag) & Utility::to_underlying(underlying::PROMOTION))
            == Utility::to_underlying(underlying::PROMOTION);
    }

    constexpr PieceType get_promtion_piecetype() const noexcept {
        return PieceType::from_ordinal((Utility::to_underlying(move_flag) & 0b11) + 1);
    }

    static constexpr MoveFlag from_ordinal(auto ordinal) {
        return static_cast<underlying>(ordinal);
    }
};

class Move {
   private:
    // Move byte format
    // Flag: xxxx
    // From:     xxxxxx
    // To:             xxxxxx
    std::uint16_t move;

   public:
    constexpr Move(MoveFlag flag, Square from, Square to) :
        move{static_cast<std::uint16_t>((flag.to_underlying() << 12) | (from.to_underlying() << 6)
                                        | (to.to_underlying()))} {}
};

}

#endif
