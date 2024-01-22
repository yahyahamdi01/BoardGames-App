#pragma once

#include "Checkers.hpp"
#include "CheckersView.hpp"
#include "../Controller.hpp"

#include <memory>
#include <vector>

class CheckersController: public Controller
{
    private:
        void HandleEvent(const sf::Event& event) override;

        void End() override;

        void PrintAndResetPlayer() const override;

        void SetWindowTitle() const override;

        void ResetDraw() const;
    public:
        explicit CheckersController(std::shared_ptr<Context> context);
        ~CheckersController() override = default;

        void Update() override;
};