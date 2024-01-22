#pragma once

#include "../Board.hpp"
#include "../Player.hpp"
#include "../game/GameStatus.hpp"
#include "../game/ModelFlags.hpp"

class Model
{
    protected:
        std::unique_ptr<Board> m_board;
        std::vector<std::shared_ptr<Player>> m_players;

        virtual void SelectPiece(const coord_t coord) = 0;
        virtual void DeselectPiece() = 0;
        void SelectPieceBase(const coord_t coord, GameStatus& status, ModelFlags& flags);
        void DeselectPieceBase(GameStatus& status, ModelFlags& flags) const;

        void HandleMove(const coord_t coord, ModelFlags& flags);
        void DeselectPieceIfNotReplaying(const ModelFlags& flags);
        void MoveOrDeselect(const coord_t coord, ModelFlags& flags);

        virtual bool IsMovePossible(const coord_t coord) const = 0;
        virtual void PerformMove(const coord_t coord) = 0;
        virtual void ProcessConditionalMove(const coord_t coord) = 0;
        virtual void ApplyCapture(const coord_t coord) = 0;
        virtual void HandlePieceCaptureAndReplay(const coord_t coord) = 0;
        bool IsMovePossibleBase(const coord_t coord, const GameStatus& status, const ModelFlags& flags) const;
        void PerformMoveBase(const coord_t coord, const ModelFlags& flags);
        void HandlePieceDeselectionAndUpdate(ModelFlags& flags);
        std::vector<direction_t> ValidatePieceAndMoves(const coord_t coord, const Piece* piece) const;
        std::tuple<int, int, int, int> GetCoordAndDirFromPossibleCapture(const coord_t coord, const Piece* piece) const;
        bool HasCapturingMoves(const coord_t coord) const;

        void InitBoard();
        virtual void CreateGameBoard() = 0;
        virtual void CheckBoardDimensions(const int row, const int col) const = 0;
        virtual void InitPlayers() = 0;
        void InitPlayersBase(GameStatus& status);

        void UpdatePossibleMoves() const;

        virtual void SwitchPlayer() = 0;
        void SwitchPlayerBase(GameStatus& status, ModelFlags& flags);

        virtual void CheckForWin();
        virtual void EndGameIfNoMoves() = 0;
        void EndGameIfNoPieces(int nbWhitePieces, int nbBlackPieces, GameStatus& m_status, ModelFlags& m_flags);
        void CountPieces(int& nbBlackPieces, int& nbWhitePieces) const;

        bool AreCoordinatesValid(const coord_t coord) const;
    public:
        Model() = default;
        virtual ~Model() = default;

        virtual void Turn(const coord_t coord);
        void Init();
        
        virtual void GameStart() = 0;

        virtual bool IsGameStarted() const = 0;
        virtual bool IsGameFinished() const = 0;
        virtual bool IsPieceSelected() const = 0;
        virtual bool IsSelectedPieceChanged() const = 0;
        virtual bool IsBoardNeedUpdate() const = 0;
        virtual bool IsCurrentPlayerChanged() const = 0;

        virtual void ResetCurrentPlayerChangedFlag() = 0;
        virtual void ResetSelectedPieceFlag() = 0;
        virtual void ResetBoardNeedUpdateFlag() = 0;

        Piece* GetPiece(coord_t coord) const;

        virtual Player* GetWinner() const = 0;
        
        std::vector<std::shared_ptr<Player>>& GetPlayers();
        std::unique_ptr<Board>& GetBoard();
        virtual std::shared_ptr<Player> GetCurrentPlayer() const = 0;
        virtual coord_t GetSelectedPiece() const = 0;
        virtual coord_t GetLastSelectedPiece() const = 0;
        std::vector<coord_t> GetPossibleMoves(const coord_t coord) const;
        virtual std::vector<coord_t> GetLastPossibleMoves() const = 0;
};