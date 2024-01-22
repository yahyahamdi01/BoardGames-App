#include "../../../include/game/bulltricker/BulltrickerFlags.hpp"

void BulltrickerFlags::CapturingMoveRequired()
{
    m_capturingMoveRequired = true;
}
void BulltrickerFlags::ResetCapturingMoveRequiredFlag()
{
    m_capturingMoveRequired = false;
}
bool BulltrickerFlags::IsCapturingMoveRequired() const
{
    return m_capturingMoveRequired;
}

void BulltrickerFlags::ResetFlags()
{
    ResetCapturingMoveRequiredFlag();
}