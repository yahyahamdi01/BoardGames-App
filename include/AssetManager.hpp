#pragma once

#include <map>
#include <memory>
#include <string>

#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/Font.hpp>

enum AssetID
{
    MAIN_FONT = 0,
    MENUBACKGROUND,
    CHECKERS_BLACK_PAWN,
    CHECKERS_WHITE_PAWN,
    CHECKERS_BLACK_QUEEN,
    CHECKERS_WHITE_QUEEN,
    BUTIN_BLACK_PIECE,
    BUTIN_RED_PIECE,
    BUTIN_YELLOW_PIECE,
    BULLTRICKER_WHITE_HORIZ_PIECE,
    BULLTRICKER_WHITE_VERT_PIECE,
    BULLTRICKER_BLACK_HORIZ_PIECE,
    BULLTRICKER_BLACK_VERT_PIECE,
    BULLTRICKER_WHITE_HORIZ_QUEEN,
    BULLTRICKER_WHITE_VERT_QUEEN,
    BULLTRICKER_BLACK_HORIZ_QUEEN,
    BULLTRICKER_BLACK_VERT_QUEEN,
    BULLTRICKER_WHITE_KING,
    BULLTRICKER_BLACK_KING,
    EMPTY_ASSET
};

namespace Engine
{
    class AssetManager
    {
        private:
            std::map<int, std::unique_ptr<sf::Texture>> m_textures;
            std::map<int, std::unique_ptr<sf::Font>> m_fonts;

        public:
            AssetManager();
            ~AssetManager();

            void AddTexture(int id, const std::string &filePath, bool wantRepeated = false);
            void AddFont(int id, const std::string &filePath);

            bool HasTexture(int id) const;
            bool HasFont(int id) const;

            const sf::Texture &GetTexture(int id) const;
            sf::Font &GetFont(int id);
    };
}