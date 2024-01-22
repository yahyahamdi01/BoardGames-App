#include "../../../include/game/butin/ButinFlags.hpp"

bool ButinFlags::IsFirstRound() const
{
    return m_isFirstRound;
}
void ButinFlags::EndFirstRound()
{
    m_isFirstRound = false;
}

void ButinFlags::ResetFlags()
{
    // nothing to do
}