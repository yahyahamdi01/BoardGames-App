#include "../../include/game/Model.hpp"
#include "../../include/exception/InvalidUsageException.hpp"
#include "../../include/exception/InvalidCoordinatesException.hpp"

void Model::Turn(const coord_t coord)
{
    if (IsGameFinished()) throw InvalidUsageException("Model::Turn(): Game is finished");
    if (!IsGameStarted()) throw InvalidUsageException("Model::Turn(): Game is not started");
    if (!AreCoordinatesValid(coord)) throw InvalidCoordinatesException("Model::Turn(): Invalid coordinates");
}

void Model::SelectPieceBase(const coord_t coord, GameStatus& status, ModelFlags& flags)
{
    if (flags.IsPieceSelected()) DeselectPiece();

    status.SetSelectedPiece(coord);
    auto possibleMoves = GetPossibleMoves(coord);
    status.SetPossibleMoves(possibleMoves);
    flags.PieceIsSelected();
}
void Model::DeselectPieceBase(GameStatus& status, ModelFlags& flags) const
{
    status.SaveLastPossibleMoves();
    status.SaveLastSelectedPiece();
    status.ResetSelectedPiece();
    flags.SelectPieceChanged();
    flags.PieceIsNotSelected();
}

void Model::HandleMove(const coord_t coord, ModelFlags& flags)
{
    PerformMove(coord);

    CheckForWin();

    if (flags.IsGameFinished()) return;
    if (!flags.IsReplay()) SwitchPlayer();

    flags.ResetPieceCapturedFlag();
}

void Model::DeselectPieceIfNotReplaying(const ModelFlags& flags)
{
    if (flags.IsPieceSelected() && !flags.IsReplay()) DeselectPiece();
}

void Model::MoveOrDeselect(const coord_t coord, ModelFlags& flags)
{
    if (IsMovePossible(coord)) HandleMove(coord, flags);
    else DeselectPieceIfNotReplaying(flags);
}

bool Model::IsMovePossibleBase(const coord_t coord, const GameStatus& status, const ModelFlags& flags) const
{
    if (!AreCoordinatesValid(coord)) return false;

    if (!flags.IsPieceSelected()) return false;

    auto possibleMoves = GetPossibleMoves(status.GetSelectedPiece());
    return std::find(possibleMoves.begin(), possibleMoves.end(), coord) != possibleMoves.end();
}

void Model::PerformMoveBase(const coord_t coord, const ModelFlags& flags)
{
    if (!(IsMovePossible(coord) && flags.IsPieceSelected())) 
        throw InvalidUsageException("Model::PerformMoveBase(): Move is not possible");
    if (!AreCoordinatesValid(coord)) 
        throw InvalidCoordinatesException("Model::PerformMoveBase(): Invalid coordinates");

    ProcessConditionalMove(coord);
}

void Model::HandlePieceDeselectionAndUpdate(ModelFlags& flags)
{
    DeselectPiece();
    UpdatePossibleMoves();
    flags.PieceIsCaptured();

    flags.BoardNeedUpdate();
}

std::vector<direction_t> Model::ValidatePieceAndMoves(const coord_t coord, const Piece* piece) const
{
    if (!piece) 
        throw InvalidUsageException("Model::ValidatePieceAndMoves(): piece is null");

    auto possibleMoves = piece->GetPossibleMoves();
  
    auto it = std::find(possibleMoves.begin(), possibleMoves.end(), coord);
    if (it == possibleMoves.end()) throw InvalidUsageException("Model::ValidatePieceAndMoves(): move is not possible");

    return possibleMoves;
}
std::tuple<int, int, int, int> Model::GetCoordAndDirFromPossibleCapture(const coord_t coord, const Piece* piece) const
{
    const auto possibleMoves = ValidatePieceAndMoves(coord, piece);

    auto possibleCaptures = piece->GetPossibleCaptures();
    
    auto it = std::find(possibleMoves.begin(), possibleMoves.end(), coord);
    const auto index = std::distance(possibleMoves.begin(), it);
    const auto [captx, capty] = possibleCaptures[index];

    const auto x = coord.first - captx;
    const auto y = coord.second - capty;

    return std::make_tuple(x, y, captx, capty);
}

bool Model::HasCapturingMoves(const coord_t coord) const
{
    const auto piece = m_board->GetPiece(coord);
    if (!piece) return false;

    const auto possibleCaptures = piece->GetPossibleCaptures();
    return !possibleCaptures.empty();
}

void Model::Init()
{
    InitPlayers();
    InitBoard();
    UpdatePossibleMoves();
}

void Model::InitBoard()
{
    if (m_board) m_board.reset();

    if (m_players.empty()) throw std::runtime_error("Model::InitBoard(): No players found");

    CreateGameBoard();

    int row = m_board->GetRows();
    int col = m_board->GetCols();

    CheckBoardDimensions(row, col);
}
void Model::InitPlayersBase(GameStatus& status)
{
    if (!m_players.empty()) m_players.clear();

    m_players.push_back(std::make_shared<Player>());
    m_players.push_back(std::make_shared<Player>());

    status.SetCurrentPlayer(m_players[GameConstants::PLAYER_ONEID]);
}

void Model::UpdatePossibleMoves() const
{
    const auto rows = m_board->GetRows();
    const auto columns = m_board->GetCols();

    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < columns; j++)
        {
            const auto coord = std::make_pair(i, j);
            const auto piece = m_board->GetPiece(coord);
            if (!piece) continue;

            piece->FindPossibleMoves(*m_board);
        }
    }
}

void Model::SwitchPlayerBase(GameStatus& m_status, ModelFlags& m_flags)
{
    m_status.SetCurrentPlayer(
        m_status.GetCurrentPlayer() == m_players[GameConstants::PLAYER_ONEID] ? 
            m_players[GameConstants::PLAYER_TWOID] : m_players[GameConstants::PLAYER_ONEID]
    );

    m_flags.ResetFlags();
    m_flags.CurrentPlayerChanged();
}

void Model::CheckForWin()
{
    EndGameIfNoMoves();
}

void Model::CountPieces(int& nbBlackPieces, int& nbWhitePieces) const
{
    const auto& rows{m_board->GetRows()};
    const auto& cols{m_board->GetCols()};

    for (int i{0}; i < rows; i++)
    {
        for (int j{0}; j < cols; j++) {
            const auto& piece{GetPiece(std::make_pair(i, j))};
            
            if (!piece) continue;
            if (piece->GetSymbol() == GameConstants::WHITE) nbWhitePieces++;
            else if (piece->GetSymbol() == GameConstants::BLACK) nbBlackPieces++;
        }
    }
}

void Model::EndGameIfNoPieces(int nbWhitePieces, int nbBlackPieces, GameStatus& m_status, ModelFlags& m_flags)
{
    if (nbWhitePieces == 0 || nbBlackPieces == 0)
    {
        m_status.SetWinner((nbWhitePieces == 0) ? m_players[GameConstants::PLAYER_TWOID].get() : m_players[GameConstants::PLAYER_ONEID].get());
        m_flags.GameFinished();
    }
}

bool Model::AreCoordinatesValid(const coord_t coord) const
{
    const auto rows = m_board->GetRows();
    const auto columns = m_board->GetCols();

    return coord.first >= 0
        && coord.first < rows
        && coord.second >= 0
        && coord.second < columns;
}

Piece* Model::GetPiece(coord_t coord) const
{
    if (!AreCoordinatesValid(coord)) 
        throw InvalidCoordinatesException("Model::GetPiece(): Invalid coordinates");

    return m_board->GetPiece(coord);
}

std::vector<std::shared_ptr<Player>>& Model::GetPlayers()
{
    return m_players;
}
std::unique_ptr<Board>& Model::GetBoard()
{
    return m_board;
}

std::vector<coord_t> Model::GetPossibleMoves(const coord_t coord) const
{
    const auto piece = m_board->GetPiece(coord);

    if (!piece) throw std::runtime_error("Model::GetPossibleMoves(): No piece found");

    return piece->GetPossibleMoves();
}