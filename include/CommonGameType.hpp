#pragma once

#include "Types.hpp"
#include "Board.hpp"

class CommonGameType
{
    protected:
        bool IsOpponentPiece(const coord_t srcCoord, const coord_t dstCoord, const Board& board) const;
    public:
        virtual ~CommonGameType() = default;
};