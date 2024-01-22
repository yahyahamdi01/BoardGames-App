#pragma once

#include "../ModelFlags.hpp"

class BulltrickerFlags: public ModelFlags
{   

    private:
        bool m_capturingMoveRequired{false};

    public:
        BulltrickerFlags() = default;
        ~BulltrickerFlags() override = default;
        
        /// @brief Défini l'indicateur \b m_capturingMoveRequired à \b true
        void CapturingMoveRequired();
        
        /// @brief Remet par défaut l'indicateur \b m_capturingMoveRequired
        void ResetCapturingMoveRequiredFlag();

        /// @brief Indique si un mouvement de capture est requis.
        bool IsCapturingMoveRequired() const;

        void ResetFlags() override ;
};