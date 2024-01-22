#include "../../include/game/ModelFlags.hpp"

void ModelFlags::GameStarted()
{
    if (m_isGameStarted) return;
    m_isGameStarted = true;
}
void ModelFlags::GameFinished()
{
    if (m_isGameFinished) return;
    m_isGameFinished = true;
}
void ModelFlags::PieceIsSelected()
{
    if (m_isPieceSelected) return;
    m_isPieceSelected = true;
}
void ModelFlags::PieceIsNotSelected()
{
    if (!m_isPieceSelected) return;
    m_isPieceSelected = false;
}
void ModelFlags::CurrentPlayerChanged()
{
    if (m_currentPlayerChanged) return;
    m_currentPlayerChanged = true;
}
void ModelFlags::SelectPieceChanged()
{
    if (m_selectedPieceChanged) return;
    m_selectedPieceChanged = true;
}
void ModelFlags::BoardNeedUpdate()
{
    if (m_boardNeedUpdate) return;
    m_boardNeedUpdate = true;
}
void ModelFlags::PieceIsCaptured()
{
    if (m_isPieceCaptured) return;
    m_isPieceCaptured = true;
}
void ModelFlags::NeedReplay()
{
    if (m_replay) return;
    m_replay = true;
}
bool ModelFlags::IsGameStarted() const
{
    return m_isGameStarted;
}
bool ModelFlags::IsGameFinished() const
{
    return m_isGameFinished;
}
bool ModelFlags::IsPieceSelected() const
{
    return m_isPieceSelected;
}
bool ModelFlags::IsSelectedPieceChanged() const
{
    return m_selectedPieceChanged;
}
bool ModelFlags::IsBoardNeedUpdate() const
{
    return m_boardNeedUpdate;
}
bool ModelFlags::IsCurrentPlayerChanged() const
{
    return m_currentPlayerChanged;
}
bool ModelFlags::IsPieceCaptured() const
{
    return m_isPieceCaptured;
}
bool ModelFlags::IsReplay() const
{
    return m_replay;
}
void ModelFlags::ResetPieceCapturedFlag()
{
    if (!m_isPieceCaptured) return;
    m_isPieceCaptured = false;
}
void ModelFlags::ResetCurrentPlayerChangedFlag()
{
    if (!m_currentPlayerChanged) return;
    m_currentPlayerChanged = false;
}
void ModelFlags::ResetSelectedPieceFlag()
{
    if (!m_selectedPieceChanged) return;
    m_selectedPieceChanged = false;
}
void ModelFlags::ResetBoardNeedUpdateFlag()
{
    if (!m_boardNeedUpdate) return;
    m_boardNeedUpdate = false;
}
void ModelFlags::ResetReplayFlag()
{
    if (!m_replay) return;
    m_replay = false;
}