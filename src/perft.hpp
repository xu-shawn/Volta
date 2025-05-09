#ifndef VOLTA_PERFT_HPP__
#define VOLTA_PERFT_HPP__

#include <cstdint>

#include "position.hpp"

namespace Volta {

namespace Chess {

void          split_perft(const PositionState& pos, std::int32_t depth);
std::uint64_t perft(const PositionState& pos, std::int32_t depth);

}

}

#endif
