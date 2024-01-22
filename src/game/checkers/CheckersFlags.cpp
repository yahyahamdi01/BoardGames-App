#include "../../../include/game/checkers/CheckersFlags.hpp"

void CheckersFlags::CapturingMoveRequired()
{
    m_capturingMoveRequired = true;
}
void CheckersFlags::ResetCapturingMoveRequiredFlag()
{
    m_capturingMoveRequired = false;
}
bool CheckersFlags::IsCapturingMoveRequired() const
{
    return m_capturingMoveRequired;
}

void CheckersFlags::ResetFlags()
{
    ResetCapturingMoveRequiredFlag();
}
