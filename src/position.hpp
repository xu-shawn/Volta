#ifndef VOLTA_POSITION_HPP__
#define VOLTA_POSITION_HPP__

#include <array>
#include <cctype>
#include <cstdint>
#include <iostream>
#include <string_view>

#include "bbmanip.hpp"
#include "bitboard.hpp"
#include "common.hpp"
#include "coordinates.hpp"
#include "move.hpp"
#include "piece.hpp"

namespace Volta::Chess {

struct PositionState {
   private:
    Square       en_passant_destination_;
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
        en_passant_destination_{},
        rule50{},
        side_to_move{Color::WHITE()},
        by_color{},
        by_piece_type{},
        mailbox{} {};

    Piece piece_on(const Square square) const noexcept;
    void  make_move(const Move move) noexcept;
    bool  is_legal() const noexcept;
    bool  is_ok() const noexcept;

    static constexpr PositionState from_fen(std::string_view fen) noexcept {
        PositionState ret{};

        constexpr std::string_view    delim  = " ";
        std::vector<std::string_view> slices = Utility::split(fen, ' ');

        assert(slices.size() == 6);

        std::uint8_t curr_sq_idx = Square(File::FILE_A(), Rank::RANK_8()).ordinal();

        for (const char ch : slices[0])
        {
            if (ch == '/')
            {
                curr_sq_idx -= 16;
                continue;
            }

            if (std::isdigit(ch))
            {
                curr_sq_idx += ch - '0';
                continue;
            }

            ret.add_piece(Piece::from_char(ch), Square::from_ordinal(curr_sq_idx));
            curr_sq_idx++;
        }

        switch (slices[1].front())
        {
        case 'w' :
            ret.side_to_move = Color::WHITE();
            break;
        case 'b' :
            ret.side_to_move = Color::BLACK();
            break;
        default :
            assert(false && "Fen parsing error: invalid side");
        }

        return ret;
    }

    static constexpr PositionState startpos() noexcept {
        return PositionState::from_fen("rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1");
    }

    constexpr BitBoard bb(const Color color) const noexcept {
        return by_color[color.to_underlying()];
    }

    constexpr BitBoard bb(const PieceType piece_type) const noexcept {
        return by_piece_type[piece_type.to_underlying()];
    }

    constexpr BitBoard bb(const Piece piece) const noexcept {
        return bb(piece.type()) & bb(piece.color());
    }

    template<typename... Ts>
    constexpr BitBoard bb(const Ts... args) const noexcept {
        return (bb(args) | ...);
    }

    constexpr Color stm() const noexcept { return side_to_move; }

    constexpr Square en_passant_destination() const noexcept { return en_passant_destination_; };
};

std::ostream& operator<<(std::ostream& os, const PositionState& pos);

}

#endif
