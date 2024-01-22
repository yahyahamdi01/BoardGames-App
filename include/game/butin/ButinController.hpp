#pragma once

#include "Butin.hpp"
#include "ButinView.hpp"
#include "../Controller.hpp"

#include <memory>
#include <vector>

class ButinController: public Controller
{
    private:
        void End() override;

        void HandleEvent(const sf::Event& event) override;

        void PrintAndResetPlayer() const override;

        void SetWindowTitle() const override;
    public:
        explicit ButinController(std::shared_ptr<Context> context);
        ~ButinController() override = default;
};