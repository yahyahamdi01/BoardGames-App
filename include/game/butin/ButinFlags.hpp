#pragma once

#include "../ModelFlags.hpp"

/**
 * @brief Classe contenant des indicateurs du modèle du jeu de butin.
 * 
 */
class ButinFlags: public ModelFlags
{
    private:
        /// @brief Indique si il s'agit du tour de préparation.
        bool m_isFirstRound{true};
    public:
        ButinFlags() = default;
        ~ButinFlags() override = default;

        /// @brief Indique si il s'agit du tour de préparation.
        bool IsFirstRound() const;
        /// @brief Défini l'indicateur \b m_isFirstRound à \b false
        void EndFirstRound();

        void ResetFlags() override;
};