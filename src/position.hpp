#ifndef VOLTA_POSITION_HPP__
#define VOLTA_POSITION_HPP__

#include <array>
#include <cctype>
#include <cstdint>
#include <iostream>
#include <string_view>

#include "bitboard.hpp"
#include "common.hpp"
#include "coordinates.hpp"
#include "move.hpp"
#include "piece.hpp"

namespace Volta::Chess {

struct PositionState {
   private:
    Square       en_passant_destination;
    std::uint8_t rule50;
    Color        side_to_move;

    std::array<BitBoard, Color::COUNT()>     by_color;
    std::array<BitBoard, PieceType::COUNT()> by_piece_type;
    std::array<Piece, Square::COUNT()>       mailbox;

    void add_piece(const Piece piece, const Square square) noexcept;
    void remove_piece(const Piece piece, const Square square) noexcept;

   public:
    constexpr PositionState& operator=(const PositionState& other) = default;

    constexpr PositionState() :
        en_passant_destination{},
        rule50{},
        side_to_move{Color::WHITE()},
        by_color{},
        by_piece_type{},
        mailbox{} {};

    Piece piece_on(const Square square) const noexcept;

    void make_move(const Move move) noexcept;

    static constexpr PositionState from_fen(std::string_view fen) noexcept {
        PositionState ret{};

        constexpr std::string_view    delim  = " ";
        std::vector<std::string_view> slices = Utility::split(fen, ' ');

        assert(slices.size() == 6);

        std::size_t curr_sq = 0;

        for (const char ch : slices[0])
        {
            if (ch == '/')
                continue;

            if (std::isdigit(ch))
            {
                curr_sq += ch - '0';
                continue;
            }

            ret.add_piece(Piece::from_char(ch), Square::from_ordinal(curr_sq));
            curr_sq++;
        }

        return ret;
    }

    static constexpr PositionState startpos() noexcept {
        return PositionState::from_fen("rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1");
    }

    constexpr BitBoard bb(const Color color) const { return by_color[color.to_underlying()]; }
    constexpr BitBoard bb(const PieceType piece_type) const {
        return by_piece_type[piece_type.to_underlying()];
    }

    template<typename... Ts>
    constexpr BitBoard bb(const Ts... args) const {
        return (bb(args) | ...);
    }
};

std::ostream& operator<<(std::ostream& os, const PositionState& pos);

}

#endif
