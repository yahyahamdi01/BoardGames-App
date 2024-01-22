#pragma once

#include <memory>
#include <vector>

#include "../Player.hpp"
#include "../Types.hpp"
#include "../Constants.hpp"

class GameStatus
{
    friend class Butin;
    friend class Checkers;
    friend class Bulltricker;
    friend class Model;

    protected:
        /// @brief Joueur courant.
        std::shared_ptr<Player> m_currentPlayer;
        /// @brief Coordonnées de la pièce sélectionnée.
        coord_t m_selectedPieceCoord = {-1, -1};
        /// @brief Coordonnées de la dernière pièce sélectionnée.
        coord_t m_lastSelectedPiece = {-1, -1};
        /// @brief Vecteur contenant les coordonnées des mouvements possibles.
        std::vector<coord_t> m_currentPossibleMoves;
        /// @brief Vecteur contenant les coordonnées des mouvements possibles de la dernière pièce sélectionnée.
        std::vector<coord_t> m_lastPossibleMoves;

        Player* m_winner = nullptr;

        /// @brief Défini le joueur courant.
        /// @param player Joueur courant.
        void SetCurrentPlayer(std::shared_ptr<Player> player)
        {
            m_currentPlayer = player;
        }
        /// @brief Défini les coordonnées de la pièce sélectionnée.
        /// @param coord Coordonnées de la pièce sélectionnée.
        void SetSelectedPiece(coord_t coord)
        {
            m_selectedPieceCoord = coord;
        }
        /// @brief Défini les mouvements possibles courants.
        /// @param moves Vecteur contenant les coordonnées des mouvements possibles.
        void SetPossibleMoves(std::vector<coord_t> const& moves)
        {
            m_currentPossibleMoves = moves;
        }

        /// @brief Sauvegarde les coordonnées des mouvements possibles de la dernière pièce sélectionnée.
        void SaveLastPossibleMoves() 
        {
            m_lastPossibleMoves = m_currentPossibleMoves;
        }
        /// @brief Sauvegarde les coordonnées de la dernière pièce sélectionnée.
        void SaveLastSelectedPiece()
        {
            m_lastSelectedPiece = m_selectedPieceCoord;
        }

        /// @brief Remet par défaut les coordonnées de la pièce sélectionnée.
        void ResetSelectedPiece()
        {
            m_selectedPieceCoord = {-1, -1};
        }

        std::shared_ptr<Player> GetCurrentPlayer() const
        {
            return m_currentPlayer;
        }
        coord_t GetSelectedPiece() const
        {
            return m_selectedPieceCoord;
        }
        coord_t GetLastSelectedPiece() const
        {
            return m_lastSelectedPiece;
        }
        std::vector<coord_t> GetLastPossibleMoves() const
        {
            return m_lastPossibleMoves;
        }
        Player* GetWinner() const
        {
            return m_winner;
        }
        void SetWinner(Player* winner)
        {
            m_winner = winner;
        } 
};