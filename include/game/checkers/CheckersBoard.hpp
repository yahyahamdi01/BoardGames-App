#pragma once

#include "CheckersPiece.hpp"
#include "../../Constants.hpp"
#include "../../CommonGameType.hpp"

#include <vector>

class CheckersPiece;

class CheckersBoard: public Board, public CommonGameType
{
    private:
        std::unique_ptr<Piece> CreatePiece(coord_t coord, char color) const override;
        std::unique_ptr<CheckersPiece> CreateBlackPiece(coord_t coord) const;
        std::unique_ptr<CheckersPiece> CreateWhitePiece(coord_t coord) const;
    public:
        explicit CheckersBoard(std::vector<std::shared_ptr<Player>> players);
        ~CheckersBoard() override = default;

        friend std::ostream& operator<<(std::ostream& os, const CheckersBoard& board);

        void FillBoard() override;
};