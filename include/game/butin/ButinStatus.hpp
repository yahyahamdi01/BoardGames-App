#pragma once

#include "../GameStatus.hpp"

/**
 * @class ButinStatus 
 * @brief Classe contenant des informations sur l'état du jeu.
 */
class ButinStatus: public GameStatus
{
    private:
        /// @brief Score du gagnant.
        int m_winnerScore{0};

        int m_currentPlayerIndex{0};
    public:
        void IncrementCurrentPlayerIndex()
        {
            m_currentPlayerIndex++;
        }

        void SetWinnerScore(int score)
        {
            m_winnerScore = score;
        }
        void SetCurrentPlayerIndex(int index)
        {
            m_currentPlayerIndex = index;
        }

        
        int GetWinnerScore() const
        {
            return m_winnerScore;
        }
        int GetCurrentPlayerIndex() const
        {
            return m_currentPlayerIndex;
        }
};