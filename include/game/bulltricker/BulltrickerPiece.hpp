#pragma once

#include "../../Piece.hpp"
#include "../../Constants.hpp"

enum BT_PieceType
{
    BT_EMPTY,
    BT_PAWN,
    BT_QUEEN,
    BT_KING
};

class BulltrickerPiece: public Piece
{
    private:
        bool m_isHorizontal;

        bool IsOpponentPiece(const coord_t coord, const Board& board) const;
        

        void SimpleMoves(const Board& board);
        void CaptureMoves(const Board& board) override;
        void AddPossibleMoves(const std::vector<direction_t>& directions, const Board& board);
    public:
        BulltrickerPiece(const coord_t coord, const std::shared_ptr<Player> owner, 
                         const char symbol, const int type, 
                         const bool m_isHorizontal);
        ~BulltrickerPiece() override;

        void FindPossibleMoves(const Board& board) override;
      
        void Promote();
        void OrientationHorizontal();
        void OrientationVertical();

       bool IsJumpingKing(const coord_t& destination, int dx,const Board& board) const ;
       bool IsJumpingKingBeyond(const coord_t& destination, int dx, const Board& board) const;

        bool IsPawn() const;
        bool IsQueen() const;
        bool IsKing() const;
        bool IsPromoted() const;
        bool IsHorizontal() const;
};