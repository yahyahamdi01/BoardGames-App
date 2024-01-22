#pragma once

#include <iostream>
#include <memory>
#include <SFML/Graphics/Color.hpp>

#include "Player.hpp"
#include "Board.hpp"
#include "Types.hpp"

class Board;

struct state_t {
    int m_type = 0;
    const std::shared_ptr<Player> m_owner;
    const char m_symbol;
};

class Piece 
{
    protected:
        coord_t m_coord;
        state_t m_state;

        std::vector<coord_t> m_possibleMoves;
        std::vector<direction_t> m_possibleCaptures;
    public:
        Piece(const coord_t coord, const std::shared_ptr<Player> owner, const char symbol);
        virtual ~Piece() = default;

        virtual void FindPossibleMoves(const Board& board);
        virtual void CaptureMoves(const Board& board) = 0;

        bool IsWithinBoard(const coord_t coord, const Board& board) const;
        bool IsEmptyCell(const coord_t coord, const Board& board) const;
        
        void SetPosition(const coord_t coord);

        std::vector<coord_t> GetPossibleMoves() const;
        std::vector<direction_t> GetPossibleCaptures() const;
        coord_t GetPosition() const;
        int GetX() const;
        int GetY() const;
        std::shared_ptr<Player> GetOwner() const;
        char GetSymbol() const;
        state_t GetState() const;
};