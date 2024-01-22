#include "../include/Board.hpp"

Board::Board(std::vector<std::shared_ptr<Player>> players, const int rows, const int cols):
    m_rows{rows},
    m_cols{cols},
    m_players{std::move(players)}
{}

void Board::Init()
{
    m_board.resize(m_rows);
    for (int i = 0; i < m_rows; i++)
        m_board[i].resize(m_cols);
    FillBoard();
}

void Board::MovePiece(const coord_t coord, const coord_t newCoord)
{
    CheckBounds(coord);
    CheckBounds(newCoord);

    auto piece = RemovePieceAt(coord);
    piece->SetPosition(newCoord);
    PlacePieceAt(newCoord, std::move(piece));
}
std::unique_ptr<Piece> Board::RemovePieceAt(const coord_t coord)
{
    CheckBounds(coord);

    const auto [x, y] = coord;
    auto piece = std::move(m_board[x][y]);
    m_board[x][y] = nullptr;

    return piece;
}
void Board::PlacePieceAt(const coord_t coord, std::unique_ptr<Piece> piece)
{
    CheckBounds(coord);

    const auto [x, y] = coord;
    m_board[x][y] = std::move(piece);
}

void Board::RemovePiece(const coord_t coord)
{
    CheckBounds(coord);

    const auto [x, y] = coord;
    m_board[x][y] = nullptr;
}

bool Board::IsEmptyCell(const coord_t coord) const
{
    CheckBounds(coord);

    return m_board[coord.first][coord.second] == nullptr;
}

void Board::CheckBounds(const coord_t coord) const
{
    const auto [x, y] = coord;
    if (x < 0 || x >= m_rows || y < 0 || y >= m_cols)
        throw std::out_of_range("x or y is out of range");
}

Piece* Board::GetPiece(const coord_t coord) const
{
    CheckBounds(coord);

    return m_board[coord.first][coord.second].get();
}