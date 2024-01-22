#include "../include/GameChoice.hpp"
#include "../include/game/checkers/CheckersController.hpp"
#include "../include/game/butin/ButinController.hpp"
#include "../include/game/bulltricker/BulltrickerController.hpp"
#include "../include/Constants.hpp"
#include "../include/exception/AssetNotFoundException.hpp"

#include <iostream>
#include <algorithm>
#include <SFML/Window/Event.hpp>

using namespace UIConstants;
using namespace UIConstants::GameChoiceContext;
using namespace WindowConstants;
using namespace GameChoiceConstants;

GameChoice::GameChoice(const std::shared_ptr<Context> &context): m_context(context) {}

void GameChoice::Init() 
{
    sf::Font const* font = &m_context->m_assets->GetFont(MAIN_FONT);
    CheckAssets(font, "GameChoice::Init() : font is nullptr");
    sf::Texture const* background = &m_context->m_assets->GetTexture(MENUBACKGROUND);
    CheckAssets(background, "GameChoice::Init() : background is nullptr");

    InitRectangleShape(m_background, BACKGROUND_SIZE, BACKGROUND_POSITION);
    m_background.setTexture(background);

    InitRectangleShape(m_titleBackground, TITLEBACKGROUND_SIZE, TITLEBACKGROUND_POSITION, TITLEBACKGROUND_COLOR);

    const auto functions = InitFunctions();

    for (int i = 0; i < GameChoiceConstants::NUMBER_OF_TEXTS; i++)
    {
        m_texts.emplace_back();
    }

    InitText(m_texts[GameChoiceTextID::TITLEID], BOARDGAMETITLE, GAMETITLE_POSITION, *font, TITLE_CHARACTER_SIZE, TITLE_COLOR);
    InitButton(GameChoiceTextID::BUTINBUTTONID, BUTINSTRING, BUTINBUTTON_POSITION, *font, functions[GameChoiceButtonID::BUTINBUTTONID], 1);
    InitButton(GameChoiceTextID::CHECKERSBUTTONID, CHECKERSSTRING, CHECKERSBUTTON_POSITION, *font, functions[GameChoiceButtonID::CHECKERSBUTTONID], 1);
    InitButton(GameChoiceTextID::BULLTRICKERBUTTONID, BULLTRICKERSTRING, BULLTRICKERBUTTON_POSITION, *font, functions[GameChoiceButtonID::BULLTRICKERBUTTONID], 1);
    InitButton(GameChoiceTextID::EXITBUTTONID, EXITSTRING, EXITBUTTON_POSITION, *font, functions[GameChoiceButtonID::EXITBUTTONID], 1);
}

template <typename T>
void GameChoice::CheckAssets(T const* ptr, const std::string& errorMessage) const
{
    if (!ptr)
    {
        throw AssetNotFoundException(errorMessage);
    }
}

void GameChoice::Update()
{
    for (const auto& state : m_buttons)
        UpdateButtonState(state->m_button, state->m_isSelected, state->m_isHovered, state->m_wasHovered);

    UpdateButtonPushed();
}

void GameChoice::ProcessInput()
{
    sf::Event event;

    while (m_context->m_window->pollEvent(event)) 
    {
        if (event.type == sf::Event::Closed)
        {
            m_context->CloseWindow();
        }

        UpdateButtonHoverState(event);

        if (event.type == sf::Event::MouseMoved)
        {
            UpdateButtonSelectionState();
        }
        else if (event.type == sf::Event::MouseButtonPressed) 
        {
            HandleMousePressed(event);
        }
    }
}

void GameChoice::UpdateButtonHoverState(const sf::Event& event)
{
    for (const auto& state : m_buttons)
        state->m_isHovered = IsButtonHovered(state->m_button, event);
}

void GameChoice::UpdateButtonSelectionState()
{
    for (const auto& state : m_buttons)
        state->m_isSelected = IsButtonSelected(state->m_button, *m_context->m_window);
}

void GameChoice::HandleMousePressed(const sf::Event& event)
{
    bool isMousePressed = event.mouseButton.button == sf::Mouse::Left;
    if (isMousePressed)
    {
        auto it = std::find_if(m_buttons.begin(), m_buttons.end(), [](const auto& state) { return state->m_isSelected; });
        if (it != m_buttons.end()) (*it)->m_isPressed = true;
    }
}

void GameChoice::UpdateButtonPushed()
{
    auto it = std::find_if(m_buttons.begin(), m_buttons.end(), [](const auto& state) { return state->m_isPressed; });
    if (it != m_buttons.end())
    {
        (*it)->m_action();
        (*it)->m_isPressed = false;
    }
}

void GameChoice::Draw()
{
    m_context->m_window->clear();

    m_context->m_window->draw(m_background);
    m_context->m_window->draw(m_titleBackground);

    for (const auto& text : m_texts)
        m_context->m_window->draw(text);

    m_context->m_window->display();
}

std::array<std::function<void()>, GameChoiceConstants::NUMBER_OF_BUTTONS> GameChoice::InitFunctions()
{
    std::array<std::function<void()>, GameChoiceConstants::NUMBER_OF_BUTTONS> functions = 
    {
        [this]() { m_context->m_states->Add(std::make_unique<ButinController>(m_context), true); },
        [this]() { m_context->m_states->Add(std::make_unique<CheckersController>(m_context), true); },
        [this]() { m_context->m_states->Add(std::make_unique<BulltrickerController>(m_context), true); },
        [this]() { m_context->CloseWindow(); }
    };

    return functions;
}