#include "../../../include/game/checkers/CheckersPiece.hpp"

CheckersPiece::CheckersPiece(const coord_t coord, const std::shared_ptr<Player> owner, const char symbol): 
    Piece{coord, owner, symbol}
{
    m_state.m_type = PieceType::PAWN;
}

CheckersPiece::~CheckersPiece() {}

void CheckersPiece::FindPossibleMoves(const Board& board)
{
    Piece::FindPossibleMoves(board);

    if (m_possibleCaptures.empty())
        SimpleMoves(board);
}

void CheckersPiece::SimpleMoves(const Board& board) 
{
    const auto white{GameConstants::WHITE};
    const auto black{GameConstants::BLACK};
    const auto& wdir{GameConstants::CheckersConstants::WHITE_DIRECTION};
    const auto& bdir{GameConstants::CheckersConstants::BLACK_DIRECTION};

    std::vector<direction_t> const* directions;
    if (m_state.m_type == PieceType::PAWN)
    {
        if (m_state.m_symbol == white)
            directions = &wdir;
        else if (m_state.m_symbol == black)
            directions = &bdir;
        else
            return; 
    }
    else 
    {
        directions = &GameConstants::CheckersConstants::ALL_DIRECTION;
    }

    AddPossibleMoves(*directions, board);
}

void CheckersPiece::AddPossibleMoves(const std::vector<direction_t>& directions, const Board& board)
{
    for (const auto& [dx, dy]: directions)
    {
        int x{GetX() + dx};
        int y{GetY() + dy};

        auto coord{std::make_pair(x, y)};
        while (IsWithinBoard(coord, board) && IsEmptyCell(coord, board))
        {
            const auto& move{std::make_pair(x, y)};
            m_possibleMoves.push_back(move);
            
            if (!IsPromoted()) break;
            
            x += dx;
            y += dy;

            coord = std::make_pair(x, y);
        }
    }
}

void CheckersPiece::CaptureMoves(const Board& board)
{
    std::vector<direction_t> const* directions{&GameConstants::CheckersConstants::ALL_DIRECTION};

    if (m_state.m_type == PieceType::PAWN)
    {
        for (const auto& [dx, dy]: *directions)
        {
            int x{GetX() + 2*dx};
            int y{GetY() + 2*dy};

            const auto& coord{std::make_pair(x, y)};
            const auto& opponentCoord{std::make_pair(GetX() + dx, GetY() + dy)};
            if (IsWithinBoard(coord, board) && IsOpponentPiece(opponentCoord, board) && IsEmptyCell(coord, board))
            {
                const auto& direction{std::make_pair(dx, dy)};
                m_possibleMoves.push_back(coord);
                m_possibleCaptures.push_back(direction);
            }
        }
    }
    else
    {
        for (const auto& dir: *directions)
        {
            QueenCaptureDirections(dir, board);
        }
    }
}

void CheckersPiece::QueenCaptureDirections(const direction_t dir, const Board& board)
{
    const auto& [dx, dy]{dir};
    int x{GetX() + dx};
    int y{GetY() + dy};

    auto coord{std::make_pair(x, y)};
    while (IsWithinBoard(coord, board) && IsEmptyCell(coord, board))
    {
        x += dx;
        y += dy;

        coord = std::make_pair(x, y);
    }

    if (IsWithinBoard(coord, board) && IsOpponentPiece(coord, board))
    {
        int captX{x + dx};
        int captY{y + dy};

        auto captCoord{std::make_pair(captX, captY)};
        while (IsWithinBoard(captCoord, board) && IsEmptyCell(captCoord, board))
        {
            m_possibleMoves.push_back(captCoord);
            m_possibleCaptures.push_back(std::make_pair(dx, dy));

            captX += dx;
            captY += dy;

            captCoord = std::make_pair(captX, captY);
        }
    }
}

bool CheckersPiece::IsOpponentPiece(const coord_t coord, const Board& board) const
{
    if (IsWithinBoard(coord, board)) 
    {
        const auto piece = board.GetPiece(coord);
        if (piece == nullptr) return false;
        const auto pieceColor = piece->GetSymbol();
        return pieceColor != m_state.m_symbol;
    }

    return false;
}

void CheckersPiece::Promote()
{
    m_state.m_type = PieceType::QUEEN;
}

bool CheckersPiece::IsPromoted() const
{
    return m_state.m_type == PieceType::QUEEN;
}

std::ostream& operator<<(std::ostream& os, const CheckersPiece& piece)
{
    os << piece.m_state.m_symbol;

    return os;
}