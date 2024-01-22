#pragma once

#include "../../Piece.hpp"
#include "../../Board.hpp"
#include "../../Constants.hpp"

class ButinBoard;

class ButinPiece: public Piece
{
    private:
        void CaptureMoves(const Board& board) override;
    public:
        ButinPiece(const coord_t coord, const char symbol);
        ~ButinPiece() override;

        friend std::ostream& operator<<(std::ostream& os, const ButinPiece& piece);
};
