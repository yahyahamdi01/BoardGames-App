#pragma once

#include "BulltrickerPiece.hpp"
#include "../../Constants.hpp"
#include "../../CommonGameType.hpp"

#include <vector>

class BulltrickerPiece;

class BulltrickerBoard: public Board, public CommonGameType
{
    private:
        std::unique_ptr<Piece> CreatePiece(const coord_t coord, const char color) const override;
        std::unique_ptr<BulltrickerPiece> CreateBlackPiece(const coord_t coord, const int type, const bool isHorizontal) const;
        std::unique_ptr<BulltrickerPiece> CreateWhitePiece(const coord_t coord, const int type, const bool isHorizontal) const;

        void PlacePieces(const int startRow, const int endRow, const char color);
    public:
        explicit BulltrickerBoard(std::vector<std::shared_ptr<Player>> players);
        ~BulltrickerBoard() override = default;

        friend std::ostream& operator<<(std::ostream& os, const BulltrickerBoard& board);

        void FillBoard() override;
        bool DetermineOrientation(const int row) const;
};