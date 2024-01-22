#include "../../../include/game/bulltricker/BulltrickerView.hpp"

BulltrickerView::BulltrickerView() {}
BulltrickerView::~BulltrickerView() {}

using namespace GameConstants;
using namespace BulltrickerConstants;
using namespace UIConstants;

void BulltrickerView::Init(std::shared_ptr<Context> context, const Board& board)
{
    const std::vector<int> textureIDs{
        BULLTRICKER_BLACK_HORIZ_PIECE,
        BULLTRICKER_BLACK_VERT_PIECE,
        BULLTRICKER_WHITE_HORIZ_PIECE,
        BULLTRICKER_WHITE_VERT_PIECE,
        BULLTRICKER_BLACK_HORIZ_QUEEN,
        BULLTRICKER_BLACK_VERT_QUEEN,
        BULLTRICKER_WHITE_HORIZ_QUEEN,
        BULLTRICKER_WHITE_VERT_QUEEN,
        BULLTRICKER_BLACK_KING,
        BULLTRICKER_WHITE_KING,
        EMPTY_ASSET
    };

    InitBase(context, textureIDs);
    InitBoardDiffCellSize(board);
    InitBoardDiffPieceSize(board);
}

void BulltrickerView::InitBoardDiffCellSize(const Board& board)
{
    const auto rows{board.GetRows()};
    const auto cols{board.GetCols()};

    ResizeVector(m_boardCell, rows, cols);

    const float offset = 10.f; 
    float currentX{offset};
    float currentY{offset};

    for (int i{0}; i < rows; i++)
    {
        currentX = offset;

        for (int j{0}; j < cols; j++)
        {
            const auto& coord{std::make_pair(i, j)};
            const auto& cellsize{CalculateCellSize(coord)};
            sf::Vector2f position{currentX, currentY};

            InitCell(i, j, cellsize, position);

            currentX = UpdateCurrentXPosition(currentX, cellsize.x);
        }
        currentY = UpdateCurrentYPosition(currentY, i);
    }
}

void BulltrickerView::InitBoardDiffPieceSize(const Board& board)
{
    const auto& rows{board.GetRows()};
    const auto& cols{board.GetRows()};

    ResizeVector(m_boardPiece, rows, cols);

    LoopUpdateBoard(board, rows, cols);
}

void BulltrickerView::SetupBoardPiece(const coord_t coord, const Board &board, 
                            const sf::Vector2f piecesize, const sf::Vector2f cellsize, const sf::Vector2f position)
{
    View::SetupBoardPiece(coord, board, piecesize, cellsize, position);

    const auto& [i, j]{coord};
    const auto& piece{dynamic_cast<const BulltrickerBoard&>(board).GetPiece(coord)};
    const auto& bulltrickerPiece{dynamic_cast<BulltrickerPiece*>(piece)};

    if (bulltrickerPiece)
        ChoosePieceTexture(m_boardPiece[i][j], *bulltrickerPiece);
    else 
        SetPieceTexture(m_boardPiece[i][j], EMPTY_ID);
}

void BulltrickerView::ChoosePieceTexture(sf::RectangleShape &piece, const BulltrickerPiece& bulltrickerPiece)
{
    const auto& color{bulltrickerPiece.GetSymbol()};
    const auto& isHorizontal{bulltrickerPiece.IsHorizontal()};
    const auto& isPromoted{bulltrickerPiece.IsPromoted()};

    SetPieceTexture(piece, color, isPromoted, isHorizontal);
}

float BulltrickerView::UpdateCurrentXPosition(const float currentX, const float cellwidth) const
{
    return currentX + cellwidth;
}

float BulltrickerView::UpdateCurrentYPosition(const float currentY, const int i) const
{
    return currentY + ((i % 2 == 0) ? BUTEE_SIZE.y : ALLEE_VERTICAL_SIZE.y);
}

sf::Vector2f BulltrickerView::CalculateCellSize(const coord_t coord) const
{
    const auto& [x, y]{coord};

    if (x%2 == 0 && y%2 == 0) return BUTEE_SIZE;
    else if (x%2 == 0 && y%2 != 0) return ALLEE_HORIZONTAL_SIZE;
    else if (x%2 != 0 && y%2 == 0) return ALLEE_VERTICAL_SIZE;
    else return ROYAL_SIZE;
}

sf::Vector2f BulltrickerView::CalculatePieceSize(const coord_t coord) const
{
    const auto& [x, y] = coord;

    if (x%2 == 0 && y%2 == 0) return BUTEE_PIECE_SIZE;
    else if (x%2 == 0 && y%2 != 0) return ALLEE_HORIZONTAL_PIECE_SIZE;
    else if (x%2 != 0 && y%2 == 0) return ALLEE_VERTICAL_PIECE_SIZE;
    else return ROYAL_PIECE_SIZE;
}

void BulltrickerView::UpdateBoard(const Board& board)
{
    const auto rows{board.GetRows()};
    const auto cols{board.GetRows()};

    LoopUpdateBoard(board, rows, cols);
}

void BulltrickerView::LoopUpdateBoard(const Board& board, const int rows, const int cols)
{
    const float offset{15.f};
    float currentX{offset};
    float currentY{offset};

    for (int i{0}; i < rows; i++) 
    {
        currentX = offset;

        for (int j{0}; j < cols; j++)
        {
            const auto& coord{std::make_pair(i, j)};
            const auto& piecesize{CalculatePieceSize(coord)};
            const auto& cellsize{CalculateCellSize(coord)};
            sf::Vector2f position{currentX, currentY};

            SetupBoardPiece(coord, board, piecesize, cellsize, position);

            currentX = UpdateCurrentXPosition(currentX, cellsize.x);
        }
        currentY = UpdateCurrentYPosition(currentY, i);
    }
}

void BulltrickerView::SetPieceTexture(sf::RectangleShape &piece, const char color, const bool promoted, const bool isHorizontal)
{
    int textureID;
    if (color == BLACK)
    {
        if (isHorizontal)
            textureID = promoted ? BLACKHORIZQUEEN_ID : BLACKHORIZPAWN_ID;  
        else textureID = promoted ? BLACKVERTQUEEN_ID : BLACKVERTPAWN_ID;
    }
    else if (color == WHITE)
    {
        if (isHorizontal)
            textureID = promoted ? WHITEHORIZQUEEN_ID : WHITEHORIZPAWN_ID;
        else textureID = promoted ? WHITEVERTQUEEN_ID : WHITEVERTPAWN_ID;
    }
    else textureID = EMPTY_ID;

    piece.setTexture(&m_pieceTexture[textureID]);
}

void BulltrickerView::PrintCurrentPlayer(const std::shared_ptr<Player> currentPlayer) const
{
    system("clear");
    if (currentPlayer->GetId()%2 == PLAYER_ONEID) std::cout << "Current player: White" << std::endl;
    else std::cout << "Current player: Black" << std::endl;
}

void BulltrickerView::PrintWinner(const Player* winner) const
{
    system("clear");
    std::string winnerStr;
    if (winner)
    {
        if (winner->GetId()%2 == PLAYER_ONEID) winnerStr = "White";
        else winnerStr = "Black";
        std::cout << "Winner: " << winnerStr << std::endl;
    }
    else std::cout << "Draw" << std::endl;
}

coord_t BulltrickerView::GetBoardCoord(const int x, const int y) const
{
    const auto& rows{m_boardCell.size()};
    const auto& cols{m_boardCell[0].size()};
    coord_t coord;

    for (size_t i{0}; i < rows; i++)
    {
        for(size_t j{0}; j < cols; j++)
        {
            const auto& cell{m_boardCell[i][j]};
            if (cell.getGlobalBounds().contains(x, y)) 
            {
                coord = std::make_pair(i, j);
                break;
            }
        }
    }

    return coord;
}