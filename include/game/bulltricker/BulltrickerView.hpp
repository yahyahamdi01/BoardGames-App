#pragma once

#include "BulltrickerBoard.hpp"
#include "../View.hpp"

class BulltrickerView: public View
{
    private:
        void InitBoardDiffCellSize(const Board& board);
        void InitBoardDiffPieceSize(const Board& board);
        
        sf::Vector2f CalculateCellSize(const coord_t coord) const;
        sf::Vector2f CalculatePieceSize(const coord_t coord) const;
        float UpdateCurrentXPosition(const float currentX, const float cellwidth) const;
        float UpdateCurrentYPosition(const float currentY, const int i) const;
        
        void ChoosePieceTexture(sf::RectangleShape &piece, const BulltrickerPiece& bulltrickerPiece);

        void SetupBoardPiece(const coord_t coord, const Board &board, 
                            const sf::Vector2f piecesize, const sf::Vector2f cellsize, const sf::Vector2f position) override;

        void SetPieceTexture(sf::RectangleShape &piece, const char color, const bool promoted = false, const bool isHorizontal = false) override;
    public:
        BulltrickerView();
        ~BulltrickerView() override;

        void Init(std::shared_ptr<Context> context, const Board& board) override;

        void UpdateBoard(const Board& board) override;
        void LoopUpdateBoard(const Board& board, const int rows, const int cols);

        void PrintCurrentPlayer(const std::shared_ptr<Player> currentPlayer) const override;
        void PrintWinner(const Player* winner) const override;

        coord_t GetBoardCoord(const int x, const int y) const override;
};