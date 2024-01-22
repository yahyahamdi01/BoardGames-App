#include "../include/EventHandler.hpp"

bool EventHandler::IsButtonHovered(const sf::Text& button, const sf::Event& event) const
{
    return button.getGlobalBounds().contains(
        event.mouseMove.x, event.mouseMove.y
    );
}

bool EventHandler::IsButtonSelected(const sf::Text& button, const sf::RenderWindow& window) const
{
    return button.getGlobalBounds().contains(
        static_cast<float>(sf::Mouse::getPosition(window).x), 
        static_cast<float>(sf::Mouse::getPosition(window).y)
    );
}
