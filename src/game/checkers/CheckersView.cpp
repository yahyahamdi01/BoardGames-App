#include "../../../include/game/checkers/CheckersView.hpp"
#include "../../../include/exception/AssetNotFoundException.hpp"

using namespace GameConstants;
using namespace CheckersConstants;
using namespace UIConstants;

CheckersView::CheckersView() {}

CheckersView::~CheckersView() {}

void CheckersView::Init(std::shared_ptr<Context> context, const Board& board)
{
    const std::vector<int> textureIDs{
        CHECKERS_BLACK_PAWN,
        CHECKERS_WHITE_PAWN,
        CHECKERS_BLACK_QUEEN,
        CHECKERS_WHITE_QUEEN,
        EMPTY_ASSET
    };
    
    InitBase(context, textureIDs);
    InitBoardCell(board, BOARDCELL_SIZE);
    InitBoardPiece(board, BOARDPIECE_SIZE, BOARDCELL_SIZE);
}

void CheckersView::UpdateBoard(const Board& board)
{
    UpdateBoardBase(board, BOARDPIECE_SIZE, BOARDCELL_SIZE);
}

void CheckersView::SetupBoardPiece(const coord_t coord, const Board &board, const sf::Vector2f piecesize, const sf::Vector2f cellsize, const sf::Vector2f position)
{
    View::SetupBoardPiece(coord, board, piecesize, cellsize, position);

    const auto piece{dynamic_cast<const CheckersBoard&>(board).GetPiece(coord)};
    const auto checkersPiece{dynamic_cast<const CheckersPiece*>(piece)};
    if (checkersPiece != nullptr)
        SetPieceTexture(m_boardPiece[coord.first][coord.second], checkersPiece->GetSymbol(), checkersPiece->IsPromoted());
    else SetPieceTexture(m_boardPiece[coord.first][coord.second], EMPTY_ID);
}

void CheckersView::SetPieceTexture(sf::RectangleShape &piece, const char color, const bool promoted, const bool isHorizontal)
{
    int textureID;
    if (color == BLACK)
        textureID = promoted ? BLACKQUEEN_ID : BLACKPAWN_ID;
    else if (color == WHITE)
        textureID = promoted ? WHITEQUEEN_ID : WHITEPAWN_ID;
    else textureID = EMPTY_ID;

    piece.setTexture(&m_pieceTexture[textureID]);
}

void CheckersView::PrintCurrentPlayer(const std::shared_ptr<Player> currentPlayer) const
{
    system("clear");
    if (currentPlayer->GetId()%2 == PLAYER_ONEID) std::cout << "Current player: White" << std::endl;
    else std::cout << "Current player: Black" << std::endl;
}
void CheckersView::PrintWinner(const Player* winner) const
{
    system("clear");
    std::string winnerStr;
    if (winner)
    {
        if (winner->GetId()%2 == PLAYER_ONEID) winnerStr = "White";
        else winnerStr = "Black";
    }
    else winnerStr = "No winner";

    std::cout << "Winner: " << winnerStr << std::endl;
}

coord_t CheckersView::GetBoardCoord(const int x, const int y) const 
{
    return GetBoardCoordBase(x, y, BOARDCELL_SIZE);
}