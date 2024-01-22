#pragma once

#include "../ModelFlags.hpp"

/**
 * @brief Classe contenant des indicateurs du modèle du jeu de dames.
 * 
 */
class CheckersFlags: public ModelFlags
{
    private:
        /// @brief Indique si un mouvement de capture est requis.
        bool m_capturingMoveRequired = false;
    public:
        CheckersFlags() = default;
        ~CheckersFlags() override = default;

        /// @brief Défini l'indicateur \b m_capturingMoveRequired à \b true
        void CapturingMoveRequired();
        
        /// @brief Remet par défaut l'indicateur \b m_capturingMoveRequired
        void ResetCapturingMoveRequiredFlag();

        /// @brief Indique si un mouvement de capture est requis.
        bool IsCapturingMoveRequired() const;

        void ResetFlags() override;
};