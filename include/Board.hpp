#pragma once

#include <iostream>
#include <memory>
#include <vector>

#include "Piece.hpp"
#include "Types.hpp"

class Piece;

class Board
{
    private:
        void PlacePieceAt(const coord_t coord, std::unique_ptr<Piece> piece);
        std::unique_ptr<Piece> RemovePieceAt(const coord_t coord);
    protected:
        int m_rows = -1;
        int m_cols = -1;

        std::vector<std::shared_ptr<Player>> m_players;
        std::vector<std::vector<std::unique_ptr<Piece>>> m_board;

        virtual std::unique_ptr<Piece> CreatePiece(const coord_t coord, const char color) const = 0;
    public:
        explicit Board(std::vector<std::shared_ptr<Player>> players, const int rows, const int cols);
        virtual ~Board() = default;

        void Init();
        virtual void FillBoard() = 0;
        void MovePiece(const coord_t coord, const coord_t newCoord);
        void RemovePiece(const coord_t coord);

        bool IsEmptyCell(const coord_t coord) const;
        void CheckBounds(const coord_t coord) const;

        int GetRows() const { return m_rows; };
        int GetCols() const { return m_cols; };

        Piece* GetPiece(const coord_t coord) const;
};