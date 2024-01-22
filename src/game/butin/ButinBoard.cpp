#include "../../../include/game/butin/ButinBoard.hpp"
#include "../../../include/game/butin/Butin.hpp"

#include <random>
using namespace GameConstants::ButinConstants;

ButinBoard::ButinBoard(std::vector<std::shared_ptr<Player>> players): 
    Board{std::move(players), BUTINROWS, BUTINCOLS}
{
    Init();
}

void ButinBoard::FillBoard() 
{
    const int numYellow{34};
    const int numRed{20};
    const int numBlack{10};
    const int totalPieces{numYellow + numRed + numBlack};

    std::vector<char> pieces(totalPieces);
    std::fill_n(pieces.begin(), numYellow, BUTIN_YELLOW); 
    std::fill_n(pieces.begin() + numYellow, numRed, BUTIN_RED); 
    std::fill_n(pieces.begin() + numYellow + numRed, numBlack, BUTIN_BLACK); 

    // Shuffle 
    std::random_device rd;
    std::mt19937 g(rd());
    std::shuffle(pieces.begin(), pieces.end(), g);

    // Place the pieces 
    int pieceIndex{0};
    for (int i{0}; i < m_rows; i++) {
        for (int j{0}; j < m_cols; j++) {
            const auto& coord{std::make_pair(i, j)};
            if (pieceIndex < totalPieces) {
                m_board[i][j] = CreatePiece(coord, pieces[pieceIndex]);
                pieceIndex++;
            } 
        }
    }
}

std::unique_ptr<Piece> ButinBoard::CreatePiece(const coord_t coord, const char color) const
{
    if (color == BUTIN_YELLOW)
        return CreateYellowPiece(coord);
    else if (color == BUTIN_RED)
        return CreateRedPiece(coord);
    else if (color == BUTIN_BLACK)
        return CreateBlackPiece(coord);
    else throw std::invalid_argument("Invalid color");
}

std::unique_ptr<ButinPiece> ButinBoard::CreateYellowPiece(const coord_t coord) const {
    
    return std::make_unique<ButinPiece>(coord, BUTIN_YELLOW); 
}

std::unique_ptr<ButinPiece> ButinBoard::CreateRedPiece(const coord_t coord) const {
    
    return std::make_unique<ButinPiece>(coord, BUTIN_RED); 
}

std::unique_ptr<ButinPiece> ButinBoard::CreateBlackPiece(const coord_t coord) const {
    
    return std::make_unique<ButinPiece>(coord, BUTIN_BLACK); 
}

std::ostream &operator<<(std::ostream &os, const ButinBoard &board)
{
    for (int i = 0; i < board.m_rows; i++)
    {
        for (int j = 0; j < board.m_cols; j++)
        {
            if (board.m_board[i][j] == nullptr)
                os << " ";
            else
                os << board.m_board[i][j]->GetSymbol();
        }
        os << std::endl;
    }
    return os;
}