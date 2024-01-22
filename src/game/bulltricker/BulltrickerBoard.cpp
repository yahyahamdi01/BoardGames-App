#include "../../../include/game/bulltricker/BulltrickerBoard.hpp"

using namespace GameConstants::BulltrickerConstants;

BulltrickerBoard::BulltrickerBoard(std::vector<std::shared_ptr<Player>> players)
    : Board{std::move(players), BULLTRICKERROWS, BULLTRICKERCOLS}
{
    Init();
}

void BulltrickerBoard::PlacePieces(const int startRow, const int endRow, const char color)
{
    for (int i{startRow}; i <= endRow; i++)
    {
        for (int j{0}; j < m_cols; j++)
        {
            const auto& coord{std::make_pair(i, j)};
            if (i%2 == 0 && j%2 == 0) continue;

            if ((i == startRow || i == startRow + 2) && j%2 == 0)
                m_board[i][j] = CreatePiece(coord, color);
            else if (i == startRow + 1 && j%2 != 0)
                m_board[i][j] = CreatePiece(coord, color);
        }
    }
}

void BulltrickerBoard::FillBoard()
{
    PlacePieces(1, 4, GameConstants::BLACK);

    PlacePieces(11, 14, GameConstants::WHITE);

    // Placement of the king
    m_board[1][7] = CreatePiece(std::make_pair(1, 7), GameConstants::BLACK);
    m_board[13][7] = CreatePiece(std::make_pair(13, 7), GameConstants::WHITE);
}

std::unique_ptr<Piece> BulltrickerBoard::CreatePiece(const coord_t coord, const char color) const
{
    const auto& [x, y]{coord};
    bool isHorizontal{DetermineOrientation(x)};
    
    if (color != GameConstants::BLACK && color != GameConstants::WHITE)
        throw std::invalid_argument("Invalid color");

    bool isKing{(color == GameConstants::BLACK && x == 1 && y == 7) || (color == GameConstants::WHITE && x == 13 && y == 7)};
    bool isQueen{((x == 1 || x == 13) && y%2 == 0) && !isKing};
    bool isPawn{!isKing && !isQueen};

    int type;
    if (isKing)
        type = BT_KING;
    else if (isQueen)
        type = BT_QUEEN;
    else if (isPawn)
        type = BT_PAWN;
    else throw std::invalid_argument("Invalid type");

    if (color == GameConstants::BLACK)
        return CreateBlackPiece(coord, type, isHorizontal);
    else
        return CreateWhitePiece(coord, type, isHorizontal);
}

std::unique_ptr<BulltrickerPiece> BulltrickerBoard::CreateBlackPiece(
    const coord_t coord, 
    const int type, 
    const bool isHorizontal) const
{
    return std::make_unique<BulltrickerPiece>(coord, m_players[GameConstants::PLAYER_TWOID], GameConstants::BLACK, type, isHorizontal);
}

std::unique_ptr<BulltrickerPiece> BulltrickerBoard::CreateWhitePiece(
    const coord_t coord, 
    const int type, 
    const bool isHorizontal) const
{
    return std::make_unique<BulltrickerPiece>(coord, m_players[GameConstants::PLAYER_ONEID], GameConstants::WHITE, type, isHorizontal);
}

bool BulltrickerBoard::DetermineOrientation(const int row) const
{
    return row%2 == 0;
}

std::ostream &operator<<(std::ostream &os, const BulltrickerBoard &board)
{
    for (int i{0}; i < board.m_rows; i++)
    {
        for (int j{0}; j < board.m_cols; j++)
        {
            if (board.m_board[i][j] == nullptr)
                os << ".";
            else
            {
                if (board.m_board[i][j]->GetState().m_type == BT_PAWN)
                    os << "P";
                else if (board.m_board[i][j]->GetState().m_type == BT_QUEEN)
                    os << "Q";
                else if (board.m_board[i][j]->GetState().m_type == BT_KING)
                    os << "K";
                else throw std::invalid_argument("Invalid type");
            }
        }
        os << std::endl;
    }
    return os;
}