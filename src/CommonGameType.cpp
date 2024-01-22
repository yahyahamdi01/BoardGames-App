#include "../include/CommonGameType.hpp"

bool CommonGameType::IsOpponentPiece(
    const coord_t srcCoord,
    const coord_t dstCoord, 
    const Board& board) const
{
    board.CheckBounds(srcCoord);
    board.CheckBounds(dstCoord);

    if (board.IsEmptyCell(srcCoord) || board.IsEmptyCell(dstCoord))
        return false;
    const auto srcPiece = board.GetPiece(srcCoord);
    const auto dstPiece = board.GetPiece(dstCoord);
    if (srcPiece->GetSymbol() == dstPiece->GetSymbol())
        return false;
    
    return true;
}