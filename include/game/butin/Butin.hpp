#pragma once

#include "ButinBoard.hpp"
#include "ButinStatus.hpp"
#include "ButinFlags.hpp"

#include "../Model.hpp"

#include <memory>
#include <vector>
#include <SFML/System/Vector2.hpp>

class Butin: public Model
{
    private:
        ButinStatus m_status;
        ButinFlags m_flags;

        void SelectPiece(const coord_t coord) override;

        bool IsYellowPiece(const coord_t coord) const;

        bool IsMovePossible(const coord_t coord) const override;
        void PerformMove(const coord_t coord) override;
        void ProcessConditionalMove(const coord_t coord) override;
        void ApplyCapture(const coord_t coord) override;
        void HandlePieceCaptureAndReplay(const coord_t coord) override;

        void InitPlayers() override;

        void UpdatePlayerScore(const char pieceType) const;
        
        void HandleFirstRoundSelection(const coord_t coord);
        void EndFirstRoundIfNeeded();
        void EndFirstRound();

        void EndGameIfNoMoves() override;
        void DetermineWinner();

        void CreateGameBoard() override;
        void CheckBoardDimensions(const int row, const int col) const override;
    public:
        ~Butin() override = default;

        void Turn(const coord_t coord) override;

        void GameStart() override;

        void SwitchPlayer() override;
        void DeselectPiece() override;

        bool IsFirstRound() const;
        bool IsGameStarted() const override;
        bool IsGameFinished() const override;
        bool IsPieceSelected() const override;
        bool IsSelectedPieceChanged() const override;
        bool IsBoardNeedUpdate() const override;
        bool IsCurrentPlayerChanged() const override;

        void ResetSelectedPieceFlag() override;
        void ResetBoardNeedUpdateFlag() override;
        void ResetCurrentPlayerChangedFlag() override;
        void ResetReplayFlag();

        Player* GetWinner() const override;
        int GetWinnerScore() const;

        std::shared_ptr<Player> GetCurrentPlayer() const override;
        coord_t GetSelectedPiece() const override;
        coord_t GetLastSelectedPiece() const override;
        std::vector<coord_t> GetLastPossibleMoves() const override;
};