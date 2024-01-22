#pragma once

#include "ButinPiece.hpp"
#include "../../Constants.hpp"

#include <vector>

class ButinPiece;

class ButinBoard: public Board
{
    private:
        std::unique_ptr<Piece> CreatePiece(const coord_t coord, const char color) const override;
        std::unique_ptr<ButinPiece> CreateBlackPiece(const coord_t coord) const;
        std::unique_ptr<ButinPiece> CreateRedPiece(const coord_t coord) const;
        std::unique_ptr<ButinPiece> CreateYellowPiece(const coord_t coord) const;
    public:
        explicit ButinBoard(std::vector<std::shared_ptr<Player>> players);
        ~ButinBoard() override = default;

        friend std::ostream& operator<<(std::ostream& os, const ButinBoard& board);

        void FillBoard() override;
};