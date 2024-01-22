#include "../../../include/game/checkers/Checkers.hpp"
#include "../../../include/exception/InvalidUsageException.hpp"
#include "../../../include/exception/InvalidCoordinatesException.hpp"

#include <algorithm>
#include <random>

void Checkers::Turn(const coord_t coord) {
    Model::Turn(coord);

    if (IsPieceOfCurrentPlayer(coord))
    {
        if (HasCapturingMoves(coord)) m_flags.CapturingMoveRequired();
        else m_flags.ResetCapturingMoveRequiredFlag();

        if (m_flags.IsCapturingMoveRequired() || !HavePieceWithCapturingMoves(true))
            SelectPiece(coord);
        else 
        {
            std::cout << "You must select a piece that can capture an opponent's piece" << std::endl;
            m_flags.CapturingMoveRequired();
        }
    }
    else MoveOrDeselect(coord, m_flags);
}

bool Checkers::IsPieceOfCurrentPlayer(coord_t coord) const
{
    auto piece{GetPiece(coord)};
    if (!piece) return false;
    
    auto pieceOwner{piece->GetOwner()};
    auto idPieceOwner{pieceOwner->GetId()};
    auto idCurrentPlayer{GetCurrentPlayer()->GetId()};

    return idCurrentPlayer == idPieceOwner;
}

bool Checkers::IsMovePossible(const coord_t coord) const
{
    return IsMovePossibleBase(coord, m_status, m_flags);
}

void Checkers::CheckForWin() {
    int nbWhitePieces{0};
    int nbBlackPieces{0};

    CountPieces(nbWhitePieces, nbBlackPieces);

    EndGameIfNoPieces(nbWhitePieces, nbBlackPieces, m_status, m_flags);
    
    Model::CheckForWin();
}

void Checkers::EndGameIfNoMoves()
{
    bool otherPlayerCanMove{HavePieceWithCapturingMoves(false) || HavePieceWithNonCapturingMoves(false)};
    if (!otherPlayerCanMove)
    {
        m_status.SetWinner((GetCurrentPlayer()->GetId()%2 == GameConstants::PLAYER_ONEID) ?
            m_players[GameConstants::PLAYER_ONEID].get() : m_players[GameConstants::PLAYER_TWOID].get());
        m_flags.GameFinished();
    }
}

void Checkers::SelectPiece(const coord_t coord)
{
    SelectPieceBase(coord, m_status, m_flags);
}
void Checkers::DeselectPiece()
{
    DeselectPieceBase(m_status, m_flags);
}

void Checkers::PerformMove(coord_t coord)
{
    PerformMoveBase(coord, m_flags);
}

void Checkers::ProcessConditionalMove(const coord_t coord)
{
    if (m_flags.IsCapturingMoveRequired() || m_flags.IsReplay())
    {
        if (IsCapturingMove(coord))
        {
            PerformCapturingMove(coord);

            m_flags.ResetCapturingMoveRequiredFlag();
        }
        else
        {
            std::cout << "You must capture an opponent's piece" << std::endl;
        }
    }
    else
    {
        PerformNonCapturingMove(coord);
    }
}

void Checkers::ApplyCapture(const coord_t coord)
{
    const auto& piece{GetPiece(GetSelectedPiece())};
    auto [x, y, captx, capty]{GetCoordAndDirFromPossibleCapture(coord, piece)};

    m_board->MovePiece(GetSelectedPiece(), coord);

    bool capt{false};
    while (!capt)
    {
        const auto& captureCoord{std::make_pair(x, y)};
        if (!AreCoordinatesValid(captureCoord)) 
            throw InvalidCoordinatesException("Checkers::PerformCapturingMove() : captureCoord are invalid");

        const auto& pieceCapture{GetPiece(captureCoord)};
        if (!pieceCapture)
        {
            x -= captx;
            y -= capty;
            continue;
        }
        
        if (piece->GetSymbol() != pieceCapture->GetSymbol())
        {
            m_board->RemovePiece(captureCoord);
            capt = true;
        }
        else break;
    }

    if (CanPromotePiece(coord)) PromotePiece(coord);
}

void Checkers::HandlePieceCaptureAndReplay(const coord_t coord)
{
    if (m_flags.IsPieceCaptured() && HasCapturingMoves(coord))
    {
        SelectPiece(coord);
        m_flags.NeedReplay();
    }
    else m_flags.ResetReplayFlag();

    m_flags.BoardNeedUpdate();
}

bool Checkers::IsCapturingMove(const coord_t coord) const
{
    const auto& piece{GetPiece(GetSelectedPiece())};
    if (!piece) return false;

    const auto& possibleMoves{piece->GetPossibleMoves()};

    return std::find(possibleMoves.begin(), possibleMoves.end(), coord) != possibleMoves.end();
}

void Checkers::PerformCapturingMove(coord_t coord)
{
    ApplyCapture(coord);

    HandlePieceDeselectionAndUpdate(m_flags);

    HandlePieceCaptureAndReplay(coord);
}

void Checkers::PerformNonCapturingMove(coord_t coord)
{
    const auto& piece{m_board->GetPiece(m_status.GetSelectedPiece())};
    ValidatePieceAndMoves(coord, piece);

    m_board->MovePiece(GetSelectedPiece(), coord);

    if (CanPromotePiece(coord)) PromotePiece(coord);

    HandlePieceDeselectionAndUpdate(m_flags);
}

bool Checkers::HavePieceWithMoves(bool capturing, bool checkCurrentPlayer) const
{
    const auto& rows{m_board->GetRows()};
    const auto& cols{m_board->GetCols()};

    for (int i{0}; i < rows; i++)
    {
        for (int j{0}; j < cols; j++)
        {
            auto coord{std::make_pair(i, j)};
            auto piece{GetPiece(coord)};
            if (!piece) continue;
            if ((piece->GetOwner() == GetCurrentPlayer()) != checkCurrentPlayer) continue;

            auto possibleMoves{capturing ? piece->GetPossibleCaptures() : piece->GetPossibleMoves()};
            if (!possibleMoves.empty()) return true;
        }
    }

    return false;
}
bool Checkers::HavePieceWithCapturingMoves(bool checkCurrentPlayer) const
{
    return HavePieceWithMoves(true, checkCurrentPlayer);
}
bool Checkers::HavePieceWithNonCapturingMoves(bool checkCurrentPlayer) const
{
    return HavePieceWithMoves(false, checkCurrentPlayer);
}

bool Checkers::CanPromotePiece(coord_t coord) const
{  
    // Un pion devient une dame si il atteint la dernière ligne du plateau adverse
    if (!AreCoordinatesValid(coord))
        throw InvalidCoordinatesException("Checkers::CanPromotePiece() : coord are invalid");

    const auto& piece{GetPiece(coord)};
    if (!piece) return false;

    const auto& checkersPiece{dynamic_cast<CheckersPiece*>(piece)};
    if (checkersPiece->IsPromoted()) return false;
    
    const auto& x{piece->GetX()};

    if (piece->GetSymbol() == GameConstants::WHITE) return (x == GameConstants::BOARD_UPPER_LIMIT);
    else return (x == GameConstants::CheckersConstants::BOARD_LOWER_LIMIT);
}

void Checkers::PromotePiece(coord_t coord)
{
    if (!AreCoordinatesValid(coord))
        throw InvalidCoordinatesException("Checkers::PromotePiece() : coord are invalid");

    auto piece{GetPiece(coord)};
    if (!piece) return;

    auto checkersPiece{dynamic_cast<CheckersPiece*>(piece)};
    checkersPiece->Promote();

    m_flags.BoardNeedUpdate();
}

void Checkers::SwitchPlayer()
{
    SwitchPlayerBase(m_status, m_flags);
}

void Checkers::InitPlayers() {
    InitPlayersBase(m_status);
}

void Checkers::CreateGameBoard()
{
    m_board = std::make_unique<CheckersBoard>(m_players);
}
void Checkers::CheckBoardDimensions(const int row, const int col) const
{
    if (row != GameConstants::CheckersConstants::CHECKERSROWS || col != GameConstants::CheckersConstants::CHECKERSCOLS)
        throw InvalidUsageException("Checkers::CheckBoardDimensions(): Invalid board dimensions");
}

void Checkers::GameStart()
{
    m_flags.GameStarted();
}

void Checkers::ResetCurrentPlayerChangedFlag()
{
    m_flags.ResetCurrentPlayerChangedFlag();
}
void Checkers::ResetSelectedPieceFlag()
{
    m_flags.ResetSelectedPieceFlag();
}
void Checkers::ResetBoardNeedUpdateFlag()
{
    m_flags.ResetBoardNeedUpdateFlag();
}

void Checkers::SetWhiteWantsDraw(bool whiteWantsDraw)
{
    m_status.SetWhiteWantsDraw(whiteWantsDraw);
}
void Checkers::SetBlackWantsDraw(bool blackWantsDraw)
{
    m_status.SetBlackWantsDraw(blackWantsDraw);
}

bool Checkers::IsWhiteWantsDraw() const
{
    return m_status.IsWhiteWantsDraw();
}

bool Checkers::IsBlackWantsDraw() const
{
    return m_status.IsBlackWantsDraw();
}

std::shared_ptr<Player> Checkers::GetCurrentPlayer() const
{
    return m_status.GetCurrentPlayer();
}
Player* Checkers::GetWinner() const
{
    return m_status.GetWinner();
}

bool Checkers::IsGameStarted() const
{
    return m_flags.IsGameStarted();
}
bool Checkers::IsGameFinished() const
{
    return m_flags.IsGameFinished();
}
coord_t Checkers::GetSelectedPiece() const
{
    return m_status.GetSelectedPiece();
}
coord_t Checkers::GetLastSelectedPiece() const
{
    return m_status.GetLastSelectedPiece();
}
bool Checkers::IsPieceSelected() const
{
    return m_flags.IsPieceSelected();
}
bool Checkers::IsSelectedPieceChanged() const
{
    return m_flags.IsSelectedPieceChanged();
}
std::vector<coord_t> Checkers::GetLastPossibleMoves() const
{
    return m_status.GetLastPossibleMoves();
}
bool Checkers::IsBoardNeedUpdate() const
{
    return m_flags.IsBoardNeedUpdate();
}
bool Checkers::IsCurrentPlayerChanged() const
{
    return m_flags.IsCurrentPlayerChanged();
}