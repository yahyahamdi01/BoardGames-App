#include "../../../include/game/butin/ButinView.hpp"
#include "../../../include/exception/AssetNotFoundException.hpp"

using namespace GameConstants::ButinConstants;
using namespace UIConstants;

ButinView::ButinView() {}

ButinView::~ButinView() {}

void ButinView::Init(std::shared_ptr<Context> context, const Board& board)
{
    const std::vector<int> textureIDs{
        BUTIN_YELLOW_PIECE,
        BUTIN_RED_PIECE,
        BUTIN_BLACK_PIECE,
        EMPTY_ASSET
    };

    InitBase(context, textureIDs);
    InitBoardCell(board, BOARDCELL_SIZE);
    InitBoardPiece(board, BOARDPIECE_SIZE, BOARDCELL_SIZE);
}

void ButinView::UpdateBoard(const Board& board)
{
    UpdateBoardBase(board, BOARDPIECE_SIZE, BOARDCELL_SIZE);
}

void ButinView::SetupBoardPiece(const coord_t coord, const Board &board, 
    const sf::Vector2f piecesize, const sf::Vector2f cellsize, const sf::Vector2f position)
{
    View::SetupBoardPiece(coord, board, piecesize, cellsize, position);

    const auto& piece{dynamic_cast<const ButinBoard&>(board).GetPiece(coord)};

    if (piece != nullptr)
        SetPieceTexture(m_boardPiece[coord.first][coord.second], piece->GetSymbol());
    else SetPieceTexture(m_boardPiece[coord.first][coord.second], EMPTY_ID);
}

void ButinView::SetPieceTexture(sf::RectangleShape &piece, const char color, const bool promoted, const bool isHorizontal)
{
    int textureID;
    if (color == BUTIN_YELLOW) textureID = YELLOW_PAWN_ID;
    else if (color == BUTIN_RED) textureID = RED_PAWN_ID;
    else if (color == BUTIN_BLACK) textureID = BLACK_PAWN_ID;
    else textureID = EMPTY_ID;

    piece.setTexture(&m_pieceTexture[textureID]);
}

void ButinView::PrintTurn(const std::shared_ptr<Player> currentPlayer, const std::vector<std::shared_ptr<Player>>& players) const
{
    system("clear");
    PrintCurrentPlayer(currentPlayer);
    PrintPlayersScore(players);
}
void ButinView::PrintCurrentPlayer(const std::shared_ptr<Player> currentPlayer) const
{
    system("clear");
    if (currentPlayer->GetId()%2 == GameConstants::PLAYER_ONEID) 
        std::cout << "Current player: " << GameConstants::PLAYER_ONEID << std::endl;
    else std::cout << "Current player: " << GameConstants::PLAYER_TWOID << std::endl;
}
void ButinView::PrintPlayersScore(const std::vector<std::shared_ptr<Player>>& players) const
{
    for (const auto& player : players) {
        PrintScore(player->GetScore());
    }
}
void ButinView::PrintWinner(const Player* winner) const
{
    system("clear");
    if (winner)
    {
        if (winner->GetId()%2 == GameConstants::PLAYER_ONEID) 
            std::cout << "The winner is: " << GameConstants::PLAYER_ONEID << std::endl;
        else std::cout << "The winner is: " << GameConstants::PLAYER_TWOID << std::endl;
    }
    else std::cout << "No winner determined." << std::endl;
}
void ButinView::PrintScore(int score) const{
    std::cout << "Score: " << score << std::endl;
}

coord_t ButinView::GetBoardCoord(const int x, const int y) const 
{
    return GetBoardCoordBase(x, y, BOARDCELL_SIZE);
}
