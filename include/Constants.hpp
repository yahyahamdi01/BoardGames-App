#pragma once

#include <SFML/Graphics.hpp>
#include <string>

#include "Types.hpp"

namespace WindowConstants
{
    const auto WINDOW_SIZE = sf::Vector2i{500, 600};
    const auto FRAMERATE_LIMIT = 60;
    const auto VERTICAL_SYNC_ENABLED = true;
    const auto WINDOW_POSITION = sf::Vector2i{
        static_cast<int>(sf::VideoMode::getDesktopMode().width / 2 - WINDOW_SIZE.x / 2), 
        static_cast<int>(sf::VideoMode::getDesktopMode().height / 2 - WINDOW_SIZE.y / 2)
    };
    const std::string WINDOW_TITLE = "Boardgame - Diamant/Hamdi";
    const std::string BUTIN_TITLE = "Butin - Diamant/Hamdi";
    const std::string CHECKERS_TITLE = "Les Dames - Diamant/Hamdi";
    const std::string BULLTRICKER_TITLE = "Bulltricker - Diamant/Hamdi";
};
namespace GameChoiceConstants
{
    const int NUMBER_OF_TEXTS = 5;
    const int NUMBER_OF_BUTTONS = 4;

    const std::string BOARDGAMETITLE = "Boardgame";
    const std::string BUTINSTRING = "Butin";
    const std::string CHECKERSSTRING = "Les Dames";
    const std::string BULLTRICKERSTRING = "Bulltricker";
    const std::string EXITSTRING = "Quitter";

    namespace GameChoiceTextID
    {
        const int TITLEID = 0;
        const int BUTINBUTTONID = 1;
        const int CHECKERSBUTTONID = 2;
        const int BULLTRICKERBUTTONID = 3;
        const int EXITBUTTONID = 4;
    };

    namespace GameChoiceButtonID
    {
        const int BUTINBUTTONID = 0;
        const int CHECKERSBUTTONID = 1;
        const int BULLTRICKERBUTTONID = 2;
        const int EXITBUTTONID = 3;
    };
}

namespace AssetsConstants
{
    const std::string MAIN_FONT = "assets/fonts/Nepoboy-K7Y4Z.ttf";

    const std::string MENUBACKGROUND = "assets/images/menu/background.png";
    
    const std::string CHECKERS_BLACK_PAWN = "assets/images/checkers/black_pawn.png";
    const std::string CHECKERS_WHITE_PAWN = "assets/images/checkers/white_pawn.png";
    const std::string CHECKERS_BLACK_QUEEN = "assets/images/checkers/black_queen.png";
    const std::string CHECKERS_WHITE_QUEEN = "assets/images/checkers/white_queen.png";
    
    const std::string BUTIN_YELLOW_PIECE = "assets/images/butin/yellow_piece.png";
    const std::string BUTIN_RED_PIECE = "assets/images/butin/red_piece.png";
    const std::string BUTIN_BLACK_PIECE = "assets/images/butin/black_piece.png";

    const std::string BULLTRICKER_BLACK_HORIZ_PIECE = "assets/images/bulltricker/allee_horz_black_pawn.png";
    const std::string BULLTRICKER_BLACK_VERT_PIECE = "assets/images/bulltricker/allee_vert_black_pawn.png";
    const std::string BULLTRICKER_WHITE_HORIZ_PIECE = "assets/images/bulltricker/allee_horz_white_pawn.png";
    const std::string BULLTRICKER_WHITE_VERT_PIECE = "assets/images/bulltricker/allee_vert_white_pawn.png";
    const std::string BULLTRICKER_BLACK_HORIZ_QUEEN = "assets/images/bulltricker/allee_horz_black_queen.png";
    const std::string BULLTRICKER_BLACK_VERT_QUEEN = "assets/images/bulltricker/allee_vert_black_queen.png";
    const std::string BULLTRICKER_WHITE_HORIZ_QUEEN = "assets/images/bulltricker/allee_horz_white_queen.png";
    const std::string BULLTRICKER_WHITE_VERT_QUEEN = "assets/images/bulltricker/allee_vert_white_queen.png";
    const std::string BULLTRICKER_BLACK_KING = "assets/images/bulltricker/black_king.png";
    const std::string BULLTRICKER_WHITE_KING = "assets/images/bulltricker/white_king.png";

    const std::string EMPTY_ASSET = "assets/images/empty.png";
};

namespace UIConstants {
    namespace GameContext {
        const sf::Vector2f LINESEPARATOR_SIZE = sf::Vector2f(static_cast<float>(WindowConstants::WINDOW_SIZE.x), 2.f);
        const sf::Vector2f LINESEPARATOR_POSITION = sf::Vector2f(0.f, static_cast<float>(WindowConstants::WINDOW_SIZE.y) - 100.f);
        const sf::Vector2f LAUNCHBUTTON_POSITION = sf::Vector2f(
            static_cast<float>(WindowConstants::WINDOW_SIZE.x) / 2, 
            static_cast<float>(WindowConstants::WINDOW_SIZE.y) - 80.f
        );
        const sf::Vector2f MENUBUTTON_POSITION = sf::Vector2f(
            static_cast<float>(WindowConstants::WINDOW_SIZE.x) / 2, 
            static_cast<float>(WindowConstants::WINDOW_SIZE.y) - 30.f
        );
        const sf::Vector2f MENUBUTTON_POSITION_LAUNCHED = sf::Vector2f(
            static_cast<float>(WindowConstants::WINDOW_SIZE.x) / 2,
            static_cast<float>(WindowConstants::WINDOW_SIZE.y) - 50.f
        );

        const int NUMBER_OF_BUTTONS = 2;
        const int NUMBER_OF_TEXTS = 2;

        const int LAUNCHBUTTONID = 0;
        const int MENUBUTTONID = 1;
    };
    namespace GameChoiceContext {
        const sf::Vector2f BUTINBUTTON_POSITION = sf::Vector2f(
            static_cast<float>(WindowConstants::WINDOW_SIZE.x) / 2, 
            static_cast<float>(WindowConstants::WINDOW_SIZE.y) / 2 - 25.f
        );
        const sf::Vector2f CHECKERSBUTTON_POSITION = sf::Vector2f(
            static_cast<float>(WindowConstants::WINDOW_SIZE.x) / 2, 
            static_cast<float>(WindowConstants::WINDOW_SIZE.y) / 2
        );
        const sf::Vector2f BULLTRICKERBUTTON_POSITION = sf::Vector2f(
            static_cast<float>(WindowConstants::WINDOW_SIZE.x) / 2, 
            static_cast<float>(WindowConstants::WINDOW_SIZE.y) / 2 + 25.f
        );
        
        const sf::Vector2f BACKGROUND_SIZE = sf::Vector2f(
            static_cast<float>(WindowConstants::WINDOW_SIZE.x), 
            static_cast<float>(WindowConstants::WINDOW_SIZE.y)
        );
        const sf::Vector2f BACKGROUND_POSITION = sf::Vector2f(0.f, 0.f);

        const sf::Vector2f TITLEBACKGROUND_SIZE = sf::Vector2f(
            300.f, 80.f
        );
        const sf::Vector2f TITLEBACKGROUND_POSITION = sf::Vector2f(
            100.f, 120.f
        );

        const sf::Color TITLE_COLOR = sf::Color{30, 30, 30};
        const sf::Color TITLEBACKGROUND_COLOR = sf::Color{30, 30, 30, 50};
    };
    const sf::Vector2f GAMETITLE_POSITION = sf::Vector2f(
        static_cast<float>(WindowConstants::WINDOW_SIZE.x) / 2, 
        static_cast<float>(WindowConstants::WINDOW_SIZE.y) / 2 - 150.f
    );
    const sf::Vector2f EXITBUTTON_POSITION = sf::Vector2f(
        static_cast<float>(WindowConstants::WINDOW_SIZE.x) / 2, 
        static_cast<float>(WindowConstants::WINDOW_SIZE.y) / 2 + 250.f
    );
    const int TITLE_CHARACTER_SIZE = 40;
    const int CHARACTER_SIZE = 20;
};

namespace GameConstants
{
    const sf::Color BLACKCELL_COLOR = sf::Color{112, 74, 39};
    const sf::Color WHITECELL_COLOR = sf::Color{209, 183, 151};

    const int BOARD_UPPER_LIMIT = 0;

    // Assuming the whole board is clickable
    const auto CLICKABLE_ZONE = std::make_pair(0, 480); 

    const int PLAYER_ONEID = 0;
    const int PLAYER_TWOID = 1;
    const int NONEID = 2;

    const char BLACK = 'B';
    const char WHITE = 'W';

    const sf::Color BOARDBACKGROUND_COLOR = sf::Color{46, 24, 3};
    const sf::Vector2f BOARDBACKGROUND_SIZE = sf::Vector2f{
        static_cast<float>(WindowConstants::WINDOW_SIZE.x) - 10.f, 
        static_cast<float>(WindowConstants::WINDOW_SIZE.y) - 110.f
    };
    const sf::Vector2f BOARDBACKGROUND_POSITION = sf::Vector2f{5.f, 5.f};
    const sf::Vector2f BOARDOFFSET = sf::Vector2f{10.f, 10.f};

    namespace CheckersConstants
    {
        const int CHECKERSROWS = 10;
        const int CHECKERSCOLS = 10;

        const int BLACKPAWN_ID = 0;
        const int WHITEPAWN_ID = 1;
        const int BLACKQUEEN_ID = 2;
        const int WHITEQUEEN_ID = 3;
        const int EMPTY_ID = 4;

        const int BOARD_LOWER_LIMIT = 9;

        const char NOWINNER = -1;

        const std::vector<direction_t> WHITE_DIRECTION = {{-1, -1}, {-1, 1}};
        const std::vector<direction_t> BLACK_DIRECTION = {{1, -1}, {1, 1}};
        const std::vector<direction_t> ALL_DIRECTION = {{-1, -1}, {-1, 1}, {1, -1}, {1, 1}};
        
        const sf::Vector2f BOARDCELL_SIZE = sf::Vector2f{
            (BOARDBACKGROUND_SIZE.x - 10.f) / static_cast<float>(CHECKERSROWS),
            (BOARDBACKGROUND_SIZE.y - 10.f) / static_cast<float>(CHECKERSCOLS)
        };
        const sf::Vector2f BOARDPIECE_SIZE = sf::Vector2f{
            BOARDCELL_SIZE.x - 10.f, 
            BOARDCELL_SIZE.y - 10.f
        };
    };

    namespace ButinConstants
    {
        const int BUTINROWS = 8; // Assuming an 8x8 board for Butin
        const int BUTINCOLS = 8;

        const int YELLOW_PAWN_ID = 0; // Define IDs for Butin pieces
        const int RED_PAWN_ID = 1;
        const int BLACK_PAWN_ID = 2;
        const int EMPTY_ID = 3;

        const char BUTIN_YELLOW = 'Y'; // Define character symbols for Butin pieces
        const char BUTIN_RED = 'R';
        const char BUTIN_BLACK = 'B';

        const std::vector<direction_t> ALL_DIRECTION = {{1, 0}, {-1, 0}, {0, 1}, {0, -1},    // Linear
                                                        {-1, -1}, {-1, 1}, {1, -1}, {1, 1}}; // Diagonal
        
        const sf::Vector2f BOARDCELL_SIZE = sf::Vector2f{
            (BOARDBACKGROUND_SIZE.x - 10.f) / static_cast<float>(BUTINROWS),
            (BOARDBACKGROUND_SIZE.y - 10.f) / static_cast<float>(BUTINCOLS)
        };
        const sf::Vector2f BOARDPIECE_SIZE = sf::Vector2f{
            BOARDCELL_SIZE.x - 10.f, 
            BOARDCELL_SIZE.y - 10.f
        };
    };

    namespace BulltrickerConstants
    {
        const int BULLTRICKERROWS = 15;
        const int BULLTRICKERCOLS = 15;

        const int BOARD_LOWER_LIMIT = 14;

        const int BLACKHORIZPAWN_ID = 0;
        const int BLACKVERTPAWN_ID = 1;
        const int WHITEHORIZPAWN_ID = 2;
        const int WHITEVERTPAWN_ID = 3;
        const int BLACKHORIZQUEEN_ID = 4;
        const int BLACKVERTQUEEN_ID = 5;
        const int WHITEHORIZQUEEN_ID = 6;
        const int WHITEVERTQUEEN_ID = 7;
        const int BLACKKING_ID = 8;
        const int WHITEKING_ID = 9;
        const int EMPTY_ID = 10;

        const direction_t NORTH = {-1, 0};
        const direction_t SOUTH = {1, 0};
        const direction_t EAST = {0, 1};
        const direction_t WEST = {0, -1};

        const std::vector<direction_t> WHITE_PAWN_DIR = {
            {-1, -1}, // Move up and left
            {-1, 1},  // Move up and right
            {-2, 0}   // Move straight up by two cells
        };

        const std::vector<direction_t> BLACK_PAWN_DIR = {
            {1, -1}, // Move down and left
            {1, 1},  // Move down and right
            {2, 0}   // Move straight down by two cells
        };

        const std::vector<direction_t> QUEEN_DIR = {
            {2, 0},   // Move down (y,x)
            {-2, 0},  // Move up
            {0, 2},   // Move right
            {0, -2},  // Move left
            {1, 1},   // Move down and right
            {1, -1},  // Move down and left
            {-1, 1},  // Move up and right
            {-1, -1}, // Move up and left
        };

        const  std::vector<direction_t> KING_DIR = {
            {2,0},
            {-2,0},
            {0,2},
            {0,-2},
            
        };

        const sf::Vector2f BUTEE_SIZE = sf::Vector2f{20.625f, 20.625f};
        const sf::Vector2f ROYAL_SIZE = sf::Vector2f{45.f, 45.f};
        const sf::Vector2f ALLEE_HORIZONTAL_SIZE = sf::Vector2f{45.f, 20.625f};
        const sf::Vector2f ALLEE_VERTICAL_SIZE = sf::Vector2f{20.625, 45.f};

        const sf::Vector2f BUTEE_PIECE_SIZE = sf::Vector2f{
            BUTEE_SIZE.x - 10.f, 
            BUTEE_SIZE.y - 10.f
        };
        const sf::Vector2f ROYAL_PIECE_SIZE = sf::Vector2f{
            ROYAL_SIZE.x - 10.f, 
            ROYAL_SIZE.y - 10.f
        };
        const sf::Vector2f ALLEE_HORIZONTAL_PIECE_SIZE = sf::Vector2f{
            ALLEE_HORIZONTAL_SIZE.x - 10.f, 
            ALLEE_HORIZONTAL_SIZE.y - 10.f
        };
        const sf::Vector2f ALLEE_VERTICAL_PIECE_SIZE = sf::Vector2f{
            ALLEE_VERTICAL_SIZE.x - 10.f, 
            ALLEE_VERTICAL_SIZE.y - 10.f
        };
    };
};