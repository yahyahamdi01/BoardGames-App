#pragma once

#include "ViewFlags.hpp"
#include "../Board.hpp"
#include "../UIHandler.hpp"
#include "../Constants.hpp"
#include "../Launcher.hpp"
#include "../Types.hpp"
#include "../Button.hpp"

#include <vector>
#include <SFML/Graphics.hpp>

class View: public UIHandler
{
    private:
        void InitButtons(std::shared_ptr<Context> context);
        void InitBoardBackground();
        void InitPieceTexture(const std::shared_ptr<Context> context, const std::vector<int>& textureIDs);
        void LoadTexture(const int textureID, const std::shared_ptr<Context> context);
    protected:
        sf::RectangleShape m_boardBackground;

        std::vector<sf::Texture> m_pieceTexture;

        std::vector<std::vector<sf::RectangleShape>> m_boardCell;
        std::vector<std::vector<sf::RectangleShape>> m_boardPiece;

        sf::RectangleShape m_lineSeparator;

        ViewFlags m_flags;

        void InitBase(std::shared_ptr<Context> context, const std::vector<int>& textureIDs);
        void InitBoardCell(const Board& board, const sf::Vector2f cellsize);
        void InitBoardPiece(const Board& board, const sf::Vector2f piecesize, const sf::Vector2f cellsize);
        void InitCell(const int row, const int col, const sf::Vector2f cellsize, const sf::Vector2f position);
        virtual void SetupBoardPiece(const coord_t coord, const Board &board, const sf::Vector2f piecesize, 
                                    const sf::Vector2f cellsize, const sf::Vector2f position);
        sf::Vector2f CalculatePosition(const float offset, const coord_t coord, const sf::Vector2f cellsize) const;
        
        template <typename T>
        void ResizeVector(std::vector<std::vector<T>>& vector, const int rows, const int cols) const;

        void DrawBoardCells(sf::RenderWindow& window);
        void DrawBoardPiece(sf::RenderWindow& window);

        void UpdateBoardBase(const Board& board, const sf::Vector2f piecesize, const sf::Vector2f cellsize);

        virtual void SetPieceTexture(sf::RectangleShape &piece, const char color, const bool promoted = false, const bool isHorizontal = false) = 0;
        
        coord_t GetBoardCoordBase(const int x, const int y, const sf::Vector2f cellsize) const;
    public:
        View();
        ~View() override;

        virtual void Init(std::shared_ptr<Context> context, const Board& board) = 0;
        virtual void UpdateBoard(const Board& board) = 0;

        void Draw(sf::RenderWindow& window);
        void HighlightCell(const coord_t coord, const sf::Color color);
        void RemoveHighlightCell(const coord_t coord);
        void HighlightPossibleMoves(const std::vector<coord_t>& possibleMoves);
        void RemoveHighlightPossibleMoves(const std::vector<coord_t>& possibleMoves);
        void Render() const;

        void Launch();

        void NeedHighlight();
        void RemoveHighlight();
        
        virtual coord_t GetBoardCoord(const int x, const int y) const = 0;

        virtual void PrintWinner(const Player* winner) const = 0;
        virtual void PrintCurrentPlayer(const std::shared_ptr<Player> currentPlayer) const = 0;

        void UpdateButtonSelectedFlag(const int buttonID, const bool newValue);
        void UpdateButtonHoveredFlag(const int buttonID, const bool newValue);
        void SetButtonVisibility(const int buttonID, const bool isVisible);
        void SetButtonPressed(const int buttonID, const bool isPressed);
        
        bool IsButtonSelected(const int buttonID) const;
        bool IsButtonPressed(const int buttonID) const;
        bool IsButtonVisible(const int buttonID) const;
        bool HasHighLightedCell() const;

        std::unique_ptr<Button>& GetButton(const int buttonID);
};