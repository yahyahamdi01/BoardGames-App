#include "../../../include/game/bulltricker/BulltrickerPiece.hpp"

BulltrickerPiece::BulltrickerPiece(const coord_t coord, const std::shared_ptr<Player> owner, 
                                   const char symbol, const int type, const bool isHorizontal):
    Piece{coord, owner, symbol}, m_isHorizontal{isHorizontal}
{
    m_state.m_type = type;
}
BulltrickerPiece::~BulltrickerPiece(){}

void BulltrickerPiece::FindPossibleMoves(const Board& board)
{
    Piece::FindPossibleMoves(board);

    if (m_possibleCaptures.empty())
        SimpleMoves(board);
}

void BulltrickerPiece::SimpleMoves(const Board& board) {
    const auto white{GameConstants::WHITE};
    const auto black{GameConstants::BLACK};
    const auto& wPawnDir{GameConstants::BulltrickerConstants::WHITE_PAWN_DIR};
    const auto& bPawnDir{GameConstants::BulltrickerConstants::BLACK_PAWN_DIR};
    const auto& queenDir{GameConstants::BulltrickerConstants::QUEEN_DIR};
    const auto& kingDir{GameConstants::BulltrickerConstants::KING_DIR};
    std::vector<direction_t> const* directions;
    if (IsPawn()) 
    {
        if (m_state.m_symbol == white)
            directions = &wPawnDir;
        else if (m_state.m_symbol == black)
            directions = &bPawnDir;
    }
    else if (IsQueen()) directions = &queenDir;
    else if (IsKing()) directions = &kingDir;
    else return;

    AddPossibleMoves(*directions, board);
}

void BulltrickerPiece::AddPossibleMoves(const std::vector<direction_t>& directions, const Board& board)
{
    for (const auto& [dx, dy] : directions) {
        int x{GetX() + dx};
        int y{GetY() + dy};

        auto coord = std::make_pair(x, y);
        
        
        if (IsPawn() && IsWithinBoard(coord, board) && IsEmptyCell(coord, board) )
        {
            if (IsJumpingKing(coord, dx, board)) break;
            if (IsJumpingKingBeyond(coord, dx, board)) break;
            m_possibleMoves.push_back(coord);
        }
        
        else if (IsQueen()) 
        {   if (IsJumpingKing(coord, dx, board)) continue;
            while (IsWithinBoard(coord, board) && IsEmptyCell(coord, board) ) 
            {
                m_possibleMoves.push_back(coord);
                if (dx == 1 || dx == -1 || dy == 1 || dy == -1) break; 
               
                x += dx;
                y += dy;

                coord = std::make_pair(x, y);
            }

        }else if (IsKing()) 
        {                              // if the cell in between the king actual cell and the desired cell is empty, then the king can move
            int x{GetX() + dx};
            int y{GetY() + dy};
            const auto& coord{std::make_pair(x, y)};
            const auto& inBetweenCoord{std::make_pair(GetX() + dx/2, GetY() + dy/2)};
            if (IsWithinBoard(coord, board) && IsEmptyCell(coord, board) && IsEmptyCell(inBetweenCoord, board)) 
            {
                m_possibleMoves.push_back(coord);
            }
            
            
        }
    }
}

void BulltrickerPiece::CaptureMoves(const Board& board) {

    std::vector<direction_t> const* directions{&GameConstants::BulltrickerConstants::QUEEN_DIR};

    if (m_state.m_type == BT_PieceType::BT_PAWN && !IsPromoted()) {
        int dx{(m_state.m_symbol == GameConstants::WHITE) ? -2 : 2}; // White pawns move up :-1, black pawns move down :+1
        int x{GetX() + dx};
        int y{GetY()}; // Capture frontale
        const auto opponentCoord{std::make_pair(x, y)};
        const auto landingCoord{std::make_pair(x + dx, y)};

        if (IsWithinBoard(opponentCoord, board) && IsOpponentPiece(opponentCoord, board) && 
            IsWithinBoard(landingCoord, board) && IsEmptyCell(landingCoord, board) && IsHorizontal()) {
           
            m_possibleMoves.push_back(landingCoord);
            m_possibleCaptures.emplace_back(dx, 0); 
        }
    }
    else if(m_state.m_type == BT_PieceType::BT_QUEEN || IsPromoted())
    {   
        for (const auto& [dx, dy] : *directions) {
         
            if (dx == 1 || dx == -1 || dy == 1 || dy == -1) break; // Queen can move only one cell in diagonal
           if(IsHorizontal() && (dx == 0 && (dy == 2 || dy == -2))) continue; // pas de capture en passage horizontal
            if (!IsHorizontal() && (dy == 0 && (dx == 2 || dx == -2))) continue;  // pas de capture en passage vertical

        
            int x{GetX() + 2*dx};
            int y{GetY() + 2*dy};

            const auto& coord{std::make_pair(x, y)};
            const auto& opponentCoord{std::make_pair(GetX() + dx, GetY() + dy)};
            if (IsWithinBoard(coord, board) && IsOpponentPiece(opponentCoord, board) && IsEmptyCell(coord, board))
             {
                m_possibleMoves.push_back(coord);
                m_possibleCaptures.emplace_back(dx, dy);
            }
        }
    }else if (IsKing()) return;
   
}
// le roi est en premiere cellule royale apres notre pion
bool BulltrickerPiece::IsJumpingKing(const coord_t& destination, int dx, const Board& board) const {
    
    if (GetY() != destination.second)   return false;
    if (abs(dx) == 2) {
        const auto& inBetweenCoord{std::make_pair(GetX() + dx / 2, GetY())};
        if (IsWithinBoard(inBetweenCoord, board)) 
        {
            const auto& piece = board.GetPiece(inBetweenCoord);
            if (piece != nullptr && (piece->GetSymbol() == GameConstants::BulltrickerConstants::WHITEKING_ID 
                                        || piece->GetSymbol() == GameConstants::BulltrickerConstants::BLACKKING_ID) )return true;
        }
    }
    
    return false;
}
//Le roi est dans la deuxieme cellule royale apres notre pion
bool BulltrickerPiece::IsJumpingKingBeyond(const coord_t& destination, int dx, const Board& board) const {
    // Ensure we're moving along the same column and the jump is two cells in the x-direction.
    if (GetY() != destination.second || abs(dx) != 2) return false;

    // Calculate the coordinates of the cell just beyond the destination (where the king might be).
    const auto& beyondCoord = std::make_pair(destination.first + dx / 2, destination.second);

    // Check if the beyond cell is within the board bounds.
    if (IsWithinBoard(beyondCoord, board)) {
        const auto& piece = board.GetPiece(beyondCoord);

        // If there's a piece and it's a king, then return true.
        if (piece != nullptr && (piece->GetSymbol() == GameConstants::BulltrickerConstants::WHITEKING_ID 
                                        || piece->GetSymbol() == GameConstants::BulltrickerConstants::BLACKKING_ID) ) {
            return true;
        }
    }
    
    // No king found after the jumped piece or the move is invalid.
    return false;
}




bool BulltrickerPiece::IsOpponentPiece(const coord_t coord, const Board& board) const
{
    if (IsWithinBoard(coord, board)) 
    {
        const auto piece{board.GetPiece(coord)};
        if (piece == nullptr) return false;
        const auto pieceColor{piece->GetSymbol()};
        return pieceColor != m_state.m_symbol;
    }

    return false;
}


void BulltrickerPiece::Promote()
{
    m_state.m_type = BT_QUEEN;
}

void BulltrickerPiece::OrientationHorizontal()
{
    m_isHorizontal = true;
}

void BulltrickerPiece::OrientationVertical()
{
    m_isHorizontal = false;
}

// Helper functions to determine if the piece is a pawn or a queen
bool BulltrickerPiece::IsPawn() const {
    return m_state.m_type == BT_PAWN;
}

bool BulltrickerPiece::IsQueen() const {
    return m_state.m_type == BT_QUEEN;
}

bool BulltrickerPiece::IsKing() const {
    return m_state.m_type == BT_KING;
}

bool BulltrickerPiece::IsPromoted() const
{
    return m_state.m_type == BT_QUEEN;
}

bool BulltrickerPiece::IsHorizontal() const
{
    return m_isHorizontal;
}