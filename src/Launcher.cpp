#include "../include/Launcher.hpp"
#include "../include/GameChoice.hpp"

#include <SFML/Window/Event.hpp>

using namespace WindowConstants;

Launcher::Launcher(): m_context{std::make_shared<Context>()}
{
    m_context->m_window->create(sf::VideoMode(WINDOW_SIZE.x, WINDOW_SIZE.y), WINDOW_TITLE, sf::Style::Close);
    m_context->m_window->setFramerateLimit(FRAMERATE_LIMIT);
    m_context->m_window->setVerticalSyncEnabled(VERTICAL_SYNC_ENABLED);
    m_context->m_window->setPosition(WINDOW_POSITION);
    
    InitAssets();

    m_context->m_states->Add(std::make_unique<GameChoice>(m_context));
}

Launcher::~Launcher(){}

void Launcher::Run() const
{
    while (m_context->m_window->isOpen()) {
        m_context->m_states->ProcessStateChange();
        m_context->m_states->GetCurrent()->ProcessInput();
        m_context->m_states->GetCurrent()->Update();
        m_context->m_states->GetCurrent()->Draw();
    }
}

void Launcher::InitAssets() const
{
    m_context->m_assets->AddFont(MAIN_FONT, AssetsConstants::MAIN_FONT);
    
    std::vector<std::pair<int, std::string>> assets = {
        {MENUBACKGROUND, AssetsConstants::MENUBACKGROUND},
        {CHECKERS_BLACK_PAWN, AssetsConstants::CHECKERS_BLACK_PAWN},
        {CHECKERS_WHITE_PAWN, AssetsConstants::CHECKERS_WHITE_PAWN},
        {CHECKERS_BLACK_QUEEN, AssetsConstants::CHECKERS_BLACK_QUEEN},
        {CHECKERS_WHITE_QUEEN, AssetsConstants::CHECKERS_WHITE_QUEEN},
        {BUTIN_YELLOW_PIECE, AssetsConstants::BUTIN_YELLOW_PIECE},
        {BUTIN_RED_PIECE, AssetsConstants::BUTIN_RED_PIECE},
        {BUTIN_BLACK_PIECE, AssetsConstants::BUTIN_BLACK_PIECE},
        {BULLTRICKER_BLACK_HORIZ_PIECE, AssetsConstants::BULLTRICKER_BLACK_HORIZ_PIECE},
        {BULLTRICKER_BLACK_VERT_PIECE, AssetsConstants::BULLTRICKER_BLACK_VERT_PIECE},
        {BULLTRICKER_WHITE_HORIZ_PIECE, AssetsConstants::BULLTRICKER_WHITE_HORIZ_PIECE},
        {BULLTRICKER_WHITE_VERT_PIECE, AssetsConstants::BULLTRICKER_WHITE_VERT_PIECE},
        {BULLTRICKER_BLACK_HORIZ_QUEEN, AssetsConstants::BULLTRICKER_BLACK_HORIZ_QUEEN},
        {BULLTRICKER_BLACK_VERT_QUEEN, AssetsConstants::BULLTRICKER_BLACK_VERT_QUEEN},
        {BULLTRICKER_WHITE_HORIZ_QUEEN, AssetsConstants::BULLTRICKER_WHITE_HORIZ_QUEEN},
        {BULLTRICKER_WHITE_VERT_QUEEN, AssetsConstants::BULLTRICKER_WHITE_VERT_QUEEN},
        {BULLTRICKER_BLACK_KING, AssetsConstants::BULLTRICKER_BLACK_KING},
        {BULLTRICKER_WHITE_KING, AssetsConstants::BULLTRICKER_WHITE_KING},
        {EMPTY_ASSET, AssetsConstants::EMPTY_ASSET}
    };

    for (const auto& [assetID, asset]: assets)
    {
        m_context->m_assets->AddTexture(assetID, asset);
    }
}