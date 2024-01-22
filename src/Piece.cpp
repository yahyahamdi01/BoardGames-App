#include "../include/Piece.hpp"

#include <vector>

Piece::Piece(const coord_t coord, const std::shared_ptr<Player> owner, const char symbol): 
    m_coord{coord},
    m_state{0, owner, symbol}
{}

void Piece::FindPossibleMoves(const Board& board)
{
    m_possibleMoves.clear();
    m_possibleCaptures.clear();

    CaptureMoves(board);
}

bool Piece::IsWithinBoard(const coord_t coord, const Board& board) const
{
    const auto [x, y] = coord;
    return (x >= 0 && x < board.GetRows()) && (y >= 0 && y < board.GetRows());
}
bool Piece::IsEmptyCell(const coord_t coord, const Board& board) const
{
    return IsWithinBoard(coord, board) && board.IsEmptyCell(coord);
}

void Piece::SetPosition(const coord_t coord)
{
    m_coord = coord;
}

std::vector<coord_t> Piece::GetPossibleMoves() const
{
    return m_possibleMoves;
}

std::vector<direction_t> Piece::GetPossibleCaptures() const
{
    return m_possibleCaptures;
}

coord_t Piece::GetPosition() const
{
    return m_coord;
}

int Piece::GetX() const
{
    return m_coord.first;
}

int Piece::GetY() const
{
    return m_coord.second;
}

std::shared_ptr<Player> Piece::GetOwner() const
{
    return m_state.m_owner;
}

char Piece::GetSymbol() const
{
    return m_state.m_symbol;
}

state_t Piece::GetState() const
{
    return m_state;
}