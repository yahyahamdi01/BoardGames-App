#pragma once

#include "../GameStatus.hpp"

class CheckersStatus: public GameStatus
{
    private:
        flag_t m_whiteWantsDraw = false;
        flag_t m_blackWantsDraw = false;
    public:
        void SetWhiteWantsDraw(bool whiteWantsDraw)
        {
            m_whiteWantsDraw = whiteWantsDraw;
        };
        void SetBlackWantsDraw(bool blackWantsDraw)
        {
            m_blackWantsDraw = blackWantsDraw;
        };

        bool IsWhiteWantsDraw() const
        {
            return m_whiteWantsDraw;
        };

        bool IsBlackWantsDraw() const
        {
            return m_blackWantsDraw;
        };
};