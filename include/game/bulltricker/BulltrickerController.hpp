#pragma once

#include "Bulltricker.hpp"
#include "BulltrickerView.hpp"
#include "../Controller.hpp"

#include <memory>
#include <vector>

class BulltrickerController : public Controller
{
    private:
        //void HandleEvent(const sf::Event& event) override;

        void End() override;

        void PrintAndResetPlayer() const override;

        void SetWindowTitle() const override;
    public:
        explicit BulltrickerController(std::shared_ptr<Context> context);
        ~BulltrickerController() override = default;

        void Update() override;    
};