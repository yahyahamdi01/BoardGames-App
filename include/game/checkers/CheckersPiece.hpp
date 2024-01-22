#pragma once

#include "../../Piece.hpp"
#include "../../Constants.hpp"
#include "../../Board.hpp"

class CheckersBoard;

enum PieceType
{
    EMPTY,
    PAWN,
    QUEEN
};

class CheckersPiece: public Piece
{
    private:
        bool IsOpponentPiece(const coord_t coord, const Board& board) const;
        
        void SimpleMoves(const Board& board);
        void CaptureMoves(const Board& board) override;
        void AddPossibleMoves(const std::vector<direction_t>& directions, const Board& board);
        void QueenCaptureDirections(const direction_t direction, const Board& board);
    public:
        CheckersPiece(const coord_t coord, const std::shared_ptr<Player> owner, const char symbol);
        ~CheckersPiece() override;

        friend std::ostream& operator<<(std::ostream& os, const CheckersPiece& piece);

        void FindPossibleMoves(const Board& board) override;

        void Promote();
        bool IsPromoted() const;
};
