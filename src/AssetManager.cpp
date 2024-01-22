#include "../include/AssetManager.hpp"
#include "../include/exception/PathNotFoundException.hpp"

#include <iostream>

Engine::AssetManager::AssetManager(){}

Engine::AssetManager::~AssetManager(){}

void Engine::AssetManager::AddTexture(int id, const std::string &filePath, bool wantRepeated)
{
    auto texture = std::make_unique<sf::Texture>();

    if (HasTexture(id))
    {
        std::cerr << "Texture already exists" << std::endl;
        return;
    }

    try
    {
        if (!texture->loadFromFile(filePath))
        {
            throw PathNotFoundException("Texture not found");
        }
        else
        {
            texture->setRepeated(wantRepeated);
            m_textures[id] = std::move(texture);
        }
    }
    catch (PathNotFoundException &e)
    {
        std::cerr << e.what() << std::endl;
    }
}

void Engine::AssetManager::AddFont(int id, const std::string &filePath)
{
    auto font = std::make_unique<sf::Font>();

    if (HasFont(id))
    {
        std::cerr << "Font already exists" << std::endl;
        return;
    }

    try
    {
        if (!font->loadFromFile(filePath))
        {
            throw PathNotFoundException("Font not found");
        }
        else m_fonts[id] = std::move(font);
    } 
    catch (PathNotFoundException &e)
    {
        std::cerr << e.what() << std::endl;
    }
}

bool Engine::AssetManager::HasTexture(int id) const
{
    return m_textures.find(id) != m_textures.end();
}

bool Engine::AssetManager::HasFont(int id) const
{
    return m_fonts.find(id) != m_fonts.end();
}

const sf::Texture &Engine::AssetManager::GetTexture(int id) const
{
    return *(m_textures.at(id).get());
}

sf::Font &Engine::AssetManager::GetFont(int id)
{
    return *(m_fonts.at(id).get());
}

