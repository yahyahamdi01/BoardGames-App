#pragma once

#include <SFML/Graphics.hpp>

class EventHandler
{
    public:
        virtual ~EventHandler() = default;

        virtual void UpdateButtonHoverState(const sf::Event& event) = 0;
        virtual void UpdateButtonSelectionState() = 0;
        virtual void HandleMousePressed(const sf::Event& event) = 0;
        virtual void UpdateButtonPushed() = 0;

        bool IsButtonHovered(const sf::Text& button, const sf::Event& event) const;
        bool IsButtonSelected(const sf::Text& button, const sf::RenderWindow& window) const;
};