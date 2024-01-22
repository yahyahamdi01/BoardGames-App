#include "../../../include/game/butin/Butin.hpp"
#include "../../../include/exception/InvalidUsageException.hpp"
#include "../../../include/exception/InvalidCoordinatesException.hpp"

#include <algorithm>

void Butin::Turn(const coord_t coord)
{
    Model::Turn(coord);

    if (IsFirstRound())
    {
        HandleFirstRoundSelection(coord);

        SwitchPlayer();

        EndFirstRoundIfNeeded();
    }
    else 
    {
        if (IsYellowPiece(coord) && !m_flags.IsReplay()) SelectPiece(coord);
        else MoveOrDeselect(coord, m_flags);
    }
}

void Butin::SelectPiece(const coord_t coord)
{
    SelectPieceBase(coord, m_status, m_flags);
}
void Butin::DeselectPiece()
{
    DeselectPieceBase(m_status, m_flags);
}

bool Butin::IsMovePossible(const coord_t coord) const
{
    return IsMovePossibleBase(coord, m_status, m_flags);
}

void Butin::PerformMove(const coord_t coord)
{
    PerformMoveBase(coord, m_flags);
}
void Butin::ProcessConditionalMove(const coord_t coord)
{
    ApplyCapture(coord);

    HandlePieceDeselectionAndUpdate(m_flags);

    HandlePieceCaptureAndReplay(coord);
}
void Butin::ApplyCapture(const coord_t coord)
{
    const auto& piece{GetPiece(GetSelectedPiece())};
    const auto& [x, y, captx, capty]{GetCoordAndDirFromPossibleCapture(coord, piece)};

    m_board->MovePiece(GetSelectedPiece(), coord);

    const auto& captureCoord{std::make_pair(x, y)};
    if (!AreCoordinatesValid(captureCoord)) 
        throw InvalidCoordinatesException("Butin::PerformMove() : captureCoord are invalid");
    
    const auto pieceCapture{GetPiece(captureCoord)};
    if (pieceCapture == nullptr) 
        throw InvalidUsageException("Butin::PerformMove() : pieceCapture is null");

    UpdatePlayerScore(pieceCapture->GetSymbol());
    m_board->RemovePiece(captureCoord);
}
void Butin::HandlePieceCaptureAndReplay(const coord_t coord)
{
    if (m_flags.IsPieceCaptured() && HasCapturingMoves(coord))
    {
        SelectPiece(coord);
        m_flags.NeedReplay();
    }
    else m_flags.ResetReplayFlag();

    m_flags.BoardNeedUpdate();
}

void Butin::InitPlayers()
{
    InitPlayersBase(m_status);
}

void Butin::CreateGameBoard()
{
    m_board = std::make_unique<ButinBoard>(m_players);
}
void Butin::CheckBoardDimensions(const int row, const int col) const
{
    if (row != GameConstants::ButinConstants::BUTINROWS || col != GameConstants::ButinConstants::BUTINCOLS)
        throw InvalidUsageException("Butin::CheckBoardDimensions(): Invalid board dimensions");
}

void Butin::UpdatePlayerScore(const char color) const
{
    int scoreIncrement{0};
    if (color == GameConstants::ButinConstants::BUTIN_YELLOW) scoreIncrement = 1;
    else if (color == GameConstants::ButinConstants::BUTIN_RED) scoreIncrement = 2;
    else if (color == GameConstants::ButinConstants::BUTIN_BLACK) scoreIncrement = 3;
    else return;

    m_status.GetCurrentPlayer()->AddScore(scoreIncrement);
}

void Butin::HandleFirstRoundSelection(const coord_t coord)
{
    const auto& piece{GetPiece(coord)};
    if (!piece) return;
    
    if (IsYellowPiece(coord))
    {
        m_board->RemovePiece(coord);
        m_status.IncrementCurrentPlayerIndex();
        m_flags.BoardNeedUpdate();
    }
}
void Butin::EndFirstRoundIfNeeded()
{
    int numberOfPlayers = m_players.size();
    if (m_status.GetCurrentPlayerIndex() >= numberOfPlayers)
    {
        EndFirstRound();
        m_status.SetCurrentPlayerIndex(0);
        UpdatePossibleMoves();
    }
}

void Butin::EndGameIfNoMoves()
{
    const auto& rows{m_board->GetRows()};
    const auto& cols{m_board->GetCols()};

    for (int i{0}; i < rows; i++)
    {
        for (int j{0}; j < cols; j++)
        {
            const auto coord{std::make_pair(i, j)};
            const auto piece{GetPiece(coord)};
            if (!piece) continue;

            if (IsYellowPiece(coord) && HasCapturingMoves(coord))
            {
                return;
            }
        }
    }

    DetermineWinner();
    m_flags.GameFinished();
}
void Butin::DetermineWinner()
{
    Player* winner{nullptr};
    const auto& playerOneScore{m_players[GameConstants::PLAYER_ONEID]->GetScore()};
    const auto& playerTwoScore{m_players[GameConstants::PLAYER_TWOID]->GetScore()};

    if (playerOneScore > playerTwoScore) winner = m_players[GameConstants::PLAYER_ONEID].get();
    else if (playerOneScore < playerTwoScore) winner = m_players[GameConstants::PLAYER_TWOID].get();

    m_status.SetWinner(winner);
    if (winner != nullptr)
        m_status.SetWinnerScore(winner->GetScore());
}

void Butin::SwitchPlayer()
{
    SwitchPlayerBase(m_status, m_flags);
}

bool Butin::IsYellowPiece(const coord_t coord) const
{
    const auto piece{GetPiece(coord)};
    if (!piece) return false;

    return piece->GetSymbol() == GameConstants::ButinConstants::BUTIN_YELLOW;
}

void Butin::GameStart() 
{
    m_flags.GameStarted();
}
void Butin::EndFirstRound() 
{
    m_flags.EndFirstRound();
}

bool Butin::IsGameStarted() const
{
    return m_flags.IsGameStarted();
}
bool Butin::IsGameFinished() const
{
    return m_flags.IsGameFinished();
}
bool Butin::IsFirstRound() const
{
    return m_flags.IsFirstRound();
}
bool Butin::IsPieceSelected() const 
{
    return m_flags.IsPieceSelected();
}
bool Butin::IsSelectedPieceChanged() const 
{
    return m_flags.IsSelectedPieceChanged();
}
bool Butin::IsBoardNeedUpdate() const
{
    return m_flags.IsBoardNeedUpdate();
}
bool Butin::IsCurrentPlayerChanged() const
{
    return m_flags.IsCurrentPlayerChanged();
}

void Butin::ResetSelectedPieceFlag()
{
    return m_flags.ResetSelectedPieceFlag();
}
void Butin::ResetBoardNeedUpdateFlag()
{
    return m_flags.ResetBoardNeedUpdateFlag();
}
void Butin::ResetCurrentPlayerChangedFlag()
{
    return m_flags.ResetCurrentPlayerChangedFlag();
}
void Butin::ResetReplayFlag()
{
    return m_flags.ResetReplayFlag();
}

std::shared_ptr<Player> Butin::GetCurrentPlayer() const
{
    return m_status.GetCurrentPlayer();
}
coord_t Butin::GetSelectedPiece() const
{
    return m_status.GetSelectedPiece();
}
coord_t Butin::GetLastSelectedPiece() const
{
    return m_status.GetLastSelectedPiece();
}
std::vector<coord_t> Butin::GetLastPossibleMoves() const
{
    return m_status.GetLastPossibleMoves();
}

Player* Butin::GetWinner() const
{
    return m_status.GetWinner();
}
int Butin::GetWinnerScore() const
{
    return m_status.GetWinnerScore();
}