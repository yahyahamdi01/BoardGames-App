#include "../../../include/game/bulltricker/Bulltricker.hpp"
#include "../../../include/exception/InvalidUsageException.hpp"
#include "../../../include/exception/InvalidCoordinatesException.hpp"


void Bulltricker::Turn(const coord_t coord)
{
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


bool Bulltricker::IsPieceOfCurrentPlayer(coord_t coord) const
{
    auto piece{GetPiece(coord)};
    if (!piece) return false;
    
    auto pieceOwner{piece->GetOwner()};
    auto idPieceOwner{pieceOwner->GetId()};
    auto idCurrentPlayer{GetCurrentPlayer()->GetId()};

    return idCurrentPlayer == idPieceOwner;
}

bool Bulltricker::IsMovePossible(const coord_t coord) const
{
    return IsMovePossibleBase(coord, m_status, m_flags);
}


void Bulltricker::SelectPiece(const coord_t coord)
{
    SelectPieceBase(coord, m_status, m_flags);

}

void Bulltricker::DeselectPiece()
{
    DeselectPieceBase(m_status, m_flags);
}


void Bulltricker::PerformMove(const coord_t coord)
{
    PerformMoveBase(coord, m_flags);
}

void Bulltricker::ProcessConditionalMove(const coord_t coord)
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


void Bulltricker::ApplyCapture(const coord_t coord)
{
    const auto piece{GetPiece(GetSelectedPiece())};
    auto [x, y, captx, capty]{GetCoordAndDirFromPossibleCapture(coord, piece)};

    m_board->MovePiece(GetSelectedPiece(), coord);

    bool capt{false};
    while (!capt)
    {
        const auto& captureCoord{std::make_pair(x, y)};
        if (!AreCoordinatesValid(captureCoord)) 
            throw InvalidCoordinatesException("Bulltricker::PerformCapturingMove() : captureCoord are invalid");

        const auto pieceCapture{GetPiece(captureCoord)};
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

void Bulltricker::HandlePieceCaptureAndReplay(const coord_t coord)
{
    if (m_flags.IsPieceCaptured() && HasCapturingMoves(coord))
        {
            SelectPiece(coord);
            m_flags.NeedReplay();
        }
        else m_flags.ResetReplayFlag();

        m_flags.BoardNeedUpdate();
}

bool Bulltricker::CanPromotePiece(coord_t coord) const
{  
    if (!AreCoordinatesValid(coord))
        throw InvalidCoordinatesException("Bulltricker::CanPromotePiece() : coord are invalid");

    const auto piece{GetPiece(coord)};
    if (!piece) return false;

    const auto bulltrickerPiece{dynamic_cast<BulltrickerPiece*>(piece)};
    if (bulltrickerPiece->IsPromoted()) return false;
    
    const auto x{piece->GetX()};

    if (piece->GetSymbol() == GameConstants::WHITE) 
        return (x == GameConstants::BOARD_UPPER_LIMIT);
    else 
        return (x == GameConstants::BulltrickerConstants::BOARD_LOWER_LIMIT);
}

void Bulltricker::PromotePiece(coord_t coord)
{
    if (!AreCoordinatesValid(coord))
        throw InvalidCoordinatesException("Bulltricker::PromotePiece() : coord are invalid");

    auto piece{GetPiece(coord)};
    if (!piece) return;

    auto checkersPiece{dynamic_cast<BulltrickerPiece*>(piece)};
    checkersPiece->Promote();

    m_flags.BoardNeedUpdate();
}

bool Bulltricker::IsCapturingMove(const coord_t coord) const
{
    const auto& piece{GetPiece(GetSelectedPiece())};
    if (!piece) return false;

    auto possibleMoves{piece->GetPossibleMoves()};

    return std::find(possibleMoves.begin(), possibleMoves.end(), coord) != possibleMoves.end();
}

void Bulltricker::PerformCapturingMove(coord_t coord)
{
    ApplyCapture(coord);

    HandlePieceOrientation(coord);

    HandlePieceDeselectionAndUpdate(m_flags);

    HandlePieceCaptureAndReplay(coord);
}

void Bulltricker::PerformNonCapturingMove(coord_t coord)
{
    const auto& piece{m_board->GetPiece(m_status.GetSelectedPiece())};
    ValidatePieceAndMoves(coord, piece);

    m_board->MovePiece(GetSelectedPiece(), coord);

    HandlePieceOrientation(coord);

    if (CanPromotePiece(coord)) PromotePiece(coord);

    HandlePieceDeselectionAndUpdate(m_flags);
}

void Bulltricker::HandlePieceOrientation(const coord_t coord) const
{
    auto piece{GetPiece(coord)};
    if (!piece) return;

    auto bulltrickerPiece{dynamic_cast<BulltrickerPiece*>(piece)};
    auto bulltrickerBoard{dynamic_cast<BulltrickerBoard*>(m_board.get())};
    if (bulltrickerBoard->DetermineOrientation(coord.first) && !bulltrickerPiece->IsHorizontal()) 
        bulltrickerPiece->OrientationHorizontal();
    else if (!bulltrickerBoard->DetermineOrientation(coord.first) && bulltrickerPiece->IsHorizontal()) 
        bulltrickerPiece->OrientationVertical();
}

bool Bulltricker::HavePieceWithMoves(bool capturing, bool checkCurrentPlayer) const
{
    auto rows{m_board->GetRows()};
    auto cols{m_board->GetCols()};

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
bool Bulltricker::HavePieceWithCapturingMoves(bool checkCurrentPlayer) const
{
    return HavePieceWithMoves(true, checkCurrentPlayer);
}

bool Bulltricker::HavePieceWithNonCapturingMoves(bool checkCurrentPlayer) const
{
    return HavePieceWithMoves(false, checkCurrentPlayer);
}


void Bulltricker::InitPlayers()
{
   InitPlayersBase(m_status);
}

void Bulltricker::CreateGameBoard()
{
    m_board = std::make_unique<BulltrickerBoard>(m_players);
}
void Bulltricker::CheckBoardDimensions(const int row, const int col) const
{
    if (row != GameConstants::BulltrickerConstants::BULLTRICKERROWS || 
        col != GameConstants::BulltrickerConstants::BULLTRICKERCOLS)
        throw InvalidUsageException("Bulltricker::CheckBoardDimensions() : Invalid board dimensions");
}

void Bulltricker::SwitchPlayer()
{
    SwitchPlayerBase(m_status, m_flags);
}

void Bulltricker::CheckForWin()
{
    int nbBlackPieces{0};
    int nbWhitePieces{0};

  
    EndGameIfKingCaptured();

    Model::CheckForWin();
}

void Bulltricker::EndGameIfKingCaptured()
{
    const auto& rows{m_board->GetRows()};
    const auto& cols{m_board->GetCols()};

    const std::vector<direction_t> directions{
        GameConstants::BulltrickerConstants::NORTH, 
        GameConstants::BulltrickerConstants::SOUTH, 
        GameConstants::BulltrickerConstants::EAST, 
        GameConstants::BulltrickerConstants::WEST
    };

    for (int i{0}; i < rows; i++)
    {
        for (int j{0}; j < cols; j++)
        {
            const auto& coord{std::make_pair(i, j)};
            const auto& piece{GetPiece(coord)};

            if (!piece || piece->GetState().m_type != BT_KING) continue;

            const auto& kingColor{piece->GetSymbol()};

            if (IsKingSurroundedByEnemies(coord, kingColor))
            {
                m_status.SetWinner(kingColor == GameConstants::WHITE ? m_players[GameConstants::PLAYER_TWOID].get() : m_players[GameConstants::PLAYER_ONEID].get());
                m_flags.GameFinished();
                return;
            }
        }
    }
}

bool Bulltricker::IsKingSurroundedByEnemies(const coord_t& coord, const char& kingColor) const
{
    const std::vector<direction_t> directions{
        GameConstants::BulltrickerConstants::NORTH, 
        GameConstants::BulltrickerConstants::SOUTH, 
        GameConstants::BulltrickerConstants::EAST, 
        GameConstants::BulltrickerConstants::WEST
    };

    return std::all_of(directions.begin(), directions.end(), [&](const direction_t& dir) 
    {
        const auto& coordToTest{std::make_pair(coord.first + dir.first, coord.second + dir.second)};
        if (!AreCoordinatesValid(coordToTest)) return true;

        const auto& pieceToTest{GetPiece(coordToTest)};
        return pieceToTest && pieceToTest->GetSymbol() != kingColor;
    });
}

void Bulltricker::EndGameIfNoMoves()
{
    bool otherPlayerCanMove{HavePieceWithCapturingMoves(false) || HavePieceWithNonCapturingMoves(false)};
    if (!otherPlayerCanMove)
    {
        m_status.SetWinner((GetCurrentPlayer()->GetId()%2 == GameConstants::PLAYER_ONEID) ?
            m_players[GameConstants::PLAYER_ONEID].get() : m_players[GameConstants::PLAYER_TWOID].get());
        m_flags.GameFinished();
    }
}

void Bulltricker::GameStart()
{
    m_flags.GameStarted();
}

bool Bulltricker::IsGameStarted() const
{
     return m_flags.IsGameStarted();
}

bool Bulltricker::IsGameFinished() const
{
    return m_flags.IsGameFinished();
}
bool Bulltricker::IsPieceSelected() const
{
    return m_flags.IsPieceSelected();
}
bool Bulltricker::IsSelectedPieceChanged() const
{
    return m_flags.IsSelectedPieceChanged();
}

bool Bulltricker::IsBoardNeedUpdate() const
{
    return m_flags.IsBoardNeedUpdate();
}

bool Bulltricker::IsCurrentPlayerChanged() const
{
   return m_flags.IsCurrentPlayerChanged();
}

void Bulltricker::ResetCurrentPlayerChangedFlag()
{
    m_flags.ResetCurrentPlayerChangedFlag();
}
void Bulltricker::ResetSelectedPieceFlag()
{
    m_flags.ResetSelectedPieceFlag();
}
void Bulltricker::ResetBoardNeedUpdateFlag()
{
    m_flags.ResetBoardNeedUpdateFlag();
}

Player* Bulltricker::GetWinner() const
{
    // TODO
    return nullptr;
}

std::shared_ptr<Player> Bulltricker::GetCurrentPlayer() const
{
    return m_status.GetCurrentPlayer();
}

coord_t Bulltricker::GetSelectedPiece() const
{
   return m_status.GetSelectedPiece();
}

coord_t Bulltricker::GetLastSelectedPiece() const
{
   return m_status.GetLastSelectedPiece();
}

std::vector<coord_t> Bulltricker::GetLastPossibleMoves() const
{
    return m_status.GetLastPossibleMoves();
}