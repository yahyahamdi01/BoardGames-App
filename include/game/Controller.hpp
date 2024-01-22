#pragma once

#include "../State.hpp"
#include "../UIHandler.hpp"
#include "../Launcher.hpp"
#include "../AssetManager.hpp"
#include "../EventHandler.hpp"
#include "../Constants.hpp"
#include "View.hpp"
#include "Model.hpp"

#include <memory>
#include <vector>
 
class Controller: public Engine::State, public EventHandler
{
    private:
        bool HavePieceChanged() const;
    protected:
        std::shared_ptr<Context> m_context;
        std::unique_ptr<Model> m_model;
        std::unique_ptr<View> m_view;

        void Start();
        virtual void End();

        // Event handling
        void UpdateButtonHoverState(const sf::Event& event) override;
        void UpdateButtonSelectionState() override;
        void HandleMousePressed(const sf::Event& event) override;
        void UpdateButtonPushed() override;

        // Update methods
        void UpdateHighlight() const;
        void UpdateBoard() const;
        void UpdateCurrentPlayer() const;

        void HighlightSelectedPiece() const;
        void RemoveHighlightSelectedPiece() const;

        virtual void HandleEvent(const sf::Event& event);
        void HandleMouseEvent(const sf::Event& event);

        virtual void PrintAndResetPlayer() const = 0;
        virtual void SetWindowTitle() const = 0;

        void CloseWindow() const;
        void CloseGame() const;
    public:
        explicit Controller(std::shared_ptr<Context> context, std::unique_ptr<Model> model, std::unique_ptr<View> view);
        ~Controller() override = default;

        // State handling
        void Init() override;
        void ProcessInput() override;
        void Update() override;
        void Draw() override;
};