#pragma once

#include "../Types.hpp"

/**
 * @brief Classe contenant des indicateurs des modèles.
 * 
 */
class ModelFlags
{
    friend class Butin;
    friend class Checkers;
    friend class Bulltricker;
    friend class Model;

    protected:
        /// @brief Indique si la partie a commencée.
        flag_t m_isGameStarted = false;
        /// @brief Indique si la partie est finie.
        flag_t m_isGameFinished = false;
        /// @brief Indique si une pièce est sélectionnée.
        flag_t m_isPieceSelected = false;
        /// @brief Indique si la pièce sélectionnée a changée.
        flag_t m_selectedPieceChanged = false;
        /// @brief Indique si le plateau doit être mis à jour.
        flag_t m_boardNeedUpdate = false;
        /// @brief Indique si une pièce a été capturée.
        flag_t m_isPieceCaptured = false;
        /// @brief Indique si le joueur courant a changé.
        flag_t m_currentPlayerChanged = false;
        /// @brief Indique si le joueur doit continuer sont tour pour capturer une autre piece adverse.
        flag_t m_replay = false;
    
        /// @brief Défini l'indicateur \b m_isGameStarted à \b true
        void GameStarted();
        /// @brief Défini l'indicateur \b m_isGameFinished à \b true
        void GameFinished();
        /// @brief Défini l'indicateur \b m_isPieceSelected à \b true
        void PieceIsSelected();
        /// @brief Défini l'indicateur \b m_isPieceSelected à \b false
        void PieceIsNotSelected();
        /// @brief Défini l'indicateur \b m_currentPlayerChanged à \b true
        void CurrentPlayerChanged();
        /// @brief Défini l'indicateur \b m_selectedPieceChanged à \b true
        void SelectPieceChanged();
        /// @brief Défini l'indicateur \b m_boardNeedUpdate à \b true
        void BoardNeedUpdate();
        /// @brief Défini l'indicateur \b m_isPieceCaptured à \b true
        void PieceIsCaptured();
        /// @brief Défini l'indicateur \b m_replay à \b true
        void NeedReplay();

        /// @brief Remet par défaut l'indicateur \b m_isPieceCaptured
        void ResetPieceCapturedFlag();
        /// @brief Remet par défaut l'indicateur \b m_currentPlayerChanged
        void ResetCurrentPlayerChangedFlag();
        /// @brief Remet par défaut l'indicateur \b m_selectedPieceChanged
        void ResetSelectedPieceFlag();
        /// @brief Remet par défaut l'indicateur \b m_boardNeedUpdate
        void ResetBoardNeedUpdateFlag();
        /// @brief Remet par défaut l'indicateur \b m_replay
        void ResetReplayFlag();

        /// @brief Indique si la partie a commencée.
        bool IsGameStarted() const;
        /// @brief Indique si la partie est finie.
        bool IsGameFinished() const;
        /// @brief Indique si une pièce est sélectionnée.
        bool IsPieceSelected() const;
        /// @brief Indique si la pièce sélectionnée a changée.
        bool IsSelectedPieceChanged() const;
        /// @brief Indique si le plateau doit être mis à jour.
        bool IsBoardNeedUpdate() const;
        /// @brief Indique si le joueur courant a changé. 
        bool IsCurrentPlayerChanged() const;
        /// @brief Indique si une pièce a été capturée.
        bool IsPieceCaptured() const;
        /// @brief Indique si le joueur doit continuer sont tour pour capturer une autre piece adverse.
        bool IsReplay() const;
    public:
        ModelFlags() = default;
        virtual ~ModelFlags() = default;

        virtual void ResetFlags() = 0;
};