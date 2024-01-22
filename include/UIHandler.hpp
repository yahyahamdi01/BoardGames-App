#pragma once

#include <iostream>
#include <SFML/Graphics.hpp>

#include "Launcher.hpp"
#include "Button.hpp"

class UIHandler
{
protected:
    std::vector<sf::Text> m_texts;
    std::vector<std::unique_ptr<Button>> m_buttons;

    virtual ~UIHandler() = default;
    void InitText(sf::Text &object, const std::string &text, 
                  const sf::Vector2f &position, const sf::Font& font, 
                  const int &characterSize, const sf::Color& color = sf::Color::White);
    void InitButton(size_t buttonID, const std::string& text, const sf::Vector2f& position, 
                    const sf::Font& font, const std::function<void()>& action, size_t idOffset = 0);
    void InitRectangleShape(sf::RectangleShape &object, const sf::Vector2f &size, 
                            const sf::Vector2f &position, const sf::Color &color = sf::Color::White) const;
    void UpdateButtonState(sf::Text &button, bool isSelected, bool isHovered, bool &wasHovered, bool isVisible = true) const;
};