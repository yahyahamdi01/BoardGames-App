#pragma once

#include <SFML/Graphics/Text.hpp>

class Button
{
    public:
        sf::Text& m_button;
        std::function<void()> m_action;

        bool m_isSelected = false;
        bool m_isHovered = false;
        bool m_wasHovered = false;
        bool m_isPressed = false;
        bool m_isVisible = true;
        
        explicit Button(sf::Text& button): 
            m_button{button}
        {}
};