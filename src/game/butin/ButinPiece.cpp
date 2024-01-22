#include "../../../include/game/butin/ButinPiece.hpp"
#include "../../../include/Constants.hpp"

ButinPiece::ButinPiece(const coord_t coord, char symbol):
    Piece{coord, nullptr, symbol}
{}

ButinPiece::~ButinPiece() {}

void ButinPiece::CaptureMoves(const Board& board)
{
    const std::vector<direction_t>* directions = &GameConstants::ButinConstants::ALL_DIRECTION;

    for (const auto& [dx, dy]: *directions)
    {
        const auto& [posX, posY]{GetPosition()};
        const int x{posX + 2*dx};
        const int y{posY + 2*dy};
        const int jumpX{posX + dx};
        const int jumpY{posY + dy};

        const auto& land{std::make_pair(x, y)};
        const auto& jump{std::make_pair(jumpX, jumpY)};
        if (IsWithinBoard(land, board) && IsEmptyCell(land, board) && !IsEmptyCell(jump, board))
        {
            const auto& direction{std::make_pair(dx, dy)};
            m_possibleMoves.push_back(land);
            m_possibleCaptures.push_back(direction);
        }
    }
}

std::ostream& operator<<(std::ostream& os, const ButinPiece& piece)
{
    os << piece.m_state.m_symbol;

    return os;
}