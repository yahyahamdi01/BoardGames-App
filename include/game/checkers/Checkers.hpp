#pragma once

#include "CheckersBoard.hpp"
//#include "../GameStatus.hpp"
#include "CheckersStatus.hpp"
#include "CheckersFlags.hpp"

#include "../Model.hpp"

#include <memory>
#include <vector>
#include <SFML/System/Vector2.hpp>

class Checkers: public Model
{
    private:
        CheckersStatus m_status;
        CheckersFlags m_flags;
    
        void SelectPiece(const coord_t coord) override;
        void DeselectPiece() override;

        bool IsPieceOfCurrentPlayer(coord_t coord) const;

        bool IsMovePossible(const coord_t coord) const override;
        void PerformMove(const coord_t coord) override;
        void ProcessConditionalMove(const coord_t coord) override;
        void ApplyCapture(const coord_t coord) override;
        void HandlePieceCaptureAndReplay(const coord_t coord) override;
        
        bool IsCapturingMove(coord_t coord) const;
        void PerformCapturingMove(coord_t coord);
        void PerformNonCapturingMove(coord_t coord);
        
        void InitPlayers() override;

        bool HavePieceWithMoves(bool capturing, bool checkCurrentPlayer) const;
        bool HavePieceWithCapturingMoves(bool checkCurrentPlayer) const;
        bool HavePieceWithNonCapturingMoves(bool checkCurrentPlayer) const;

        bool CanPromotePiece(coord_t coord) const;
        void PromotePiece(coord_t coord);

        void SwitchPlayer() override;

        void CheckForWin() override;
        void EndGameIfNoMoves() override;

        void CreateGameBoard() override;
        void CheckBoardDimensions(const int row, const int col) const override;
    public:
        ~Checkers() override = default;

        void Turn(const coord_t coord) override;

        void GameStart() override;
        
        bool IsGameStarted() const override;
        bool IsGameFinished() const override;
        bool IsPieceSelected() const override;
        bool IsSelectedPieceChanged() const override;
        bool IsBoardNeedUpdate() const override;
        bool IsCurrentPlayerChanged() const override;

        void ResetCurrentPlayerChangedFlag() override;
        void ResetSelectedPieceFlag() override;
        void ResetBoardNeedUpdateFlag() override;

        void SetWhiteWantsDraw(bool whiteWantsDraw);
        void SetBlackWantsDraw(bool blackWantsDraw);
        bool IsWhiteWantsDraw() const;
        bool IsBlackWantsDraw() const;

        Player* GetWinner() const override;

        std::shared_ptr<Player> GetCurrentPlayer() const override;
        coord_t GetSelectedPiece() const override;
        coord_t GetLastSelectedPiece() const override;
        std::vector<coord_t> GetLastPossibleMoves() const override;
};