#pragma once

#include <SFML/Graphics/RenderWindow.hpp>

#include "AssetManager.hpp"
#include "StateManager.hpp"
#include "Constants.hpp"

struct Context
{
    std::unique_ptr<sf::RenderWindow> m_window;
    std::unique_ptr<Engine::AssetManager> m_assets;
    std::unique_ptr<Engine::StateManager> m_states;

    Context(): 
        m_window{std::make_unique<sf::RenderWindow>()}, 
        m_assets{std::make_unique<Engine::AssetManager>()}, 
        m_states{std::make_unique<Engine::StateManager>()}
    {}

    void CloseWindow() const
    {
        m_states->PopAll();
        m_window->close();
    }
};

class Launcher
{
    private:
        std::shared_ptr<Context> m_context;
    public:
        Launcher();
        ~Launcher();
        void Run() const;
        void InitAssets() const;
};