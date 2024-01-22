#pragma once

#include "ButinBoard.hpp"
#include "../View.hpp"

#include <memory>
#include <vector>
#include <SFML/Graphics.hpp>

class ButinView: public View
{
    private:
        void SetupBoardPiece(const coord_t coord, const Board &board, 
                            const sf::Vector2f piecesize, const sf::Vector2f cellsize, const sf::Vector2f position) override;
        void SetPieceTexture(sf::RectangleShape &piece, const char color, const bool promoted = false, const bool isHorizontal = false) override;
    public:
        ButinView();
        ~ButinView() override;

        void Init(std::shared_ptr<Context> context, const Board& board) override;

        void UpdateBoard(const Board& board) override;

        void PrintTurn(const std::shared_ptr<Player> currentPlayer, const std::vector<std::shared_ptr<Player>>& players) const;
        void PrintCurrentPlayer(const std::shared_ptr<Player> currentPlayer) const override;
        void PrintPlayersScore(const std::vector<std::shared_ptr<Player>>& players) const;
        void PrintScore(const int score) const;
        void PrintWinner(const Player* winner) const override;

        coord_t GetBoardCoord(const int x, const int y) const override;
};