#include "../../include/game/View.hpp"
#include "../../include/exception/AssetNotFoundException.hpp"

using namespace UIConstants;

View::View() {}
View::~View() {}

void View::InitBase(
    std::shared_ptr<Context> context, 
    const std::vector<int>& textureIDs)
{
    InitPieceTexture(context, textureIDs);
    InitBoardBackground();

    InitRectangleShape(m_lineSeparator, GameContext::LINESEPARATOR_SIZE, GameContext::LINESEPARATOR_POSITION);

    InitButtons(context);
}

void View::InitPieceTexture(const std::shared_ptr<Context> context, const std::vector<int>& textureIDs)
{
    try
    {
        for (const auto& textureID : textureIDs) {
            LoadTexture(textureID, context);
        }
    }
    catch (AssetNotFoundException& e)
    {
        std::cerr << e.what() << '\n';
    }
}

void View::LoadTexture(const int textureID, const std::shared_ptr<Context> context)
{
    if (!context->m_assets->HasTexture(textureID)) {
        throw AssetNotFoundException("Texture not found" + std::to_string(textureID));
    }

    m_pieceTexture.push_back(context->m_assets->GetTexture(textureID));
}

void View::InitBoardBackground()
{
    InitRectangleShape(
        m_boardBackground, 
        GameConstants::BOARDBACKGROUND_SIZE, 
        GameConstants::BOARDBACKGROUND_POSITION
    );
    m_boardBackground.setFillColor(GameConstants::BOARDBACKGROUND_COLOR);
}

void View::InitBoardCell(const Board& board, const sf::Vector2f cellsize)
{
    const auto rows = board.GetRows();
    const auto cols = board.GetCols();

    ResizeVector(m_boardCell, rows, cols);

    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < cols; j++)
        {
            const auto& coord = std::make_pair(i, j);

            InitCell(i, j, cellsize, CalculatePosition(10.f, coord, cellsize));
        }
    } 
}

void View::InitBoardPiece(const Board& board, const sf::Vector2f piecesize, const sf::Vector2f cellsize)
{
    const auto rows = board.GetRows();
    const auto cols = board.GetCols();

    ResizeVector(m_boardPiece, rows, cols);

    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < cols; j++)
        {
            const auto coord = std::make_pair(i, j);
            SetupBoardPiece(coord, board, piecesize, cellsize, CalculatePosition(15.f, coord, cellsize));
        }
    }
}

void View::InitCell(const int row, const int col, const sf::Vector2f cellsize, const sf::Vector2f position)
{
    InitRectangleShape(
        m_boardCell[row][col],
        cellsize,
        position
    );

    m_boardCell[row][col].setFillColor((row + col) % 2 == 0 ? GameConstants::WHITECELL_COLOR : GameConstants::BLACKCELL_COLOR);
}

void View::InitButtons(std::shared_ptr<Context> context)
{
    sf::Font const* font = &context->m_assets->GetFont(MAIN_FONT);
    if (font == nullptr)
        throw std::runtime_error("View::InitBase() : font is nullptr");

    std::array<std::function<void()>, GameContext::NUMBER_OF_BUTTONS> functions =
    {
        [this]() { Launch(); },
        [this]() { SetButtonPressed(GameContext::MENUBUTTONID, true); }
    };

    for (int i = 0; i < GameContext::NUMBER_OF_TEXTS; i++)
    {
        m_texts.emplace_back();
    }

    InitButton(GameContext::LAUNCHBUTTONID, "Lancer la partie", GameContext::LAUNCHBUTTON_POSITION, *font, functions[GameContext::LAUNCHBUTTONID]);
    InitButton(GameContext::MENUBUTTONID, "Menu", GameContext::MENUBUTTON_POSITION, *font, functions[GameContext::MENUBUTTONID]);
}

void View::SetupBoardPiece(const coord_t coord, const Board &board, 
                        const sf::Vector2f piecesize, const sf::Vector2f cellsize, const sf::Vector2f position)
{
    const auto [i, j] = coord;
    InitRectangleShape(
        m_boardPiece[i][j],
        piecesize,
        position
    );
}

sf::Vector2f View::CalculatePosition(const float offset, const coord_t coord, const sf::Vector2f cellsize) const
{
    const auto& [i, j] = coord;
    return sf::Vector2f(
        offset + (cellsize.x * static_cast<float>(j)),
        offset + (cellsize.y * static_cast<float>(i))
    );
}

template <typename T>
void View::ResizeVector(std::vector<std::vector<T>>& vector, const int rows, const int cols) const
{
    vector.resize(rows);
    for (auto& row : vector)
        row.resize(cols);
}

void View::Draw(sf::RenderWindow& window)
{
    window.clear();

    window.draw(m_boardBackground);
    DrawBoardCells(window);
    DrawBoardPiece(window);
    window.draw(m_lineSeparator);

    for (const auto& button : m_buttons)
    {
        if (button->m_isVisible)
            window.draw(button->m_button);
    }
    window.display();
}
void View::DrawBoardCells(sf::RenderWindow& window)
{
    const auto rows = m_boardCell.size();
    const auto cols = m_boardCell[0].size();

    for (size_t i = 0; i < rows; i++) {
        for (size_t j = 0; j < cols ; j++) {
            window.draw(m_boardCell[i][j]);
        }
    }
}
void View::DrawBoardPiece(sf::RenderWindow& window)
{
    const auto rows = m_boardPiece.size();
    const auto cols = m_boardPiece[0].size();

    for (size_t i = 0; i < rows; i++) {
        for (size_t j = 0; j < cols ; j++) {
            window.draw(m_boardPiece[i][j]);
        }
    }
}

void View::UpdateBoardBase(const Board& board, const sf::Vector2f piecesize, const sf::Vector2f cellsize)
{
    const auto rows = board.GetRows();
    const auto cols = board.GetCols();

    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols ; j++) {
            const auto coord = std::make_pair(i, j);
            SetupBoardPiece(coord, board, piecesize, cellsize, CalculatePosition(15.f, coord, cellsize));
        }
    }
}

void View::HighlightCell(const coord_t coord, const sf::Color color)
{
    const auto [i, j] = coord;
    m_boardCell[i][j].setFillColor(color);
}
void View::RemoveHighlightCell(const coord_t coord)
{
    const auto [i, j] = coord;
    if ((i + j) % 2 == 0) m_boardCell[i][j].setFillColor(GameConstants::WHITECELL_COLOR);
    else m_boardCell[i][j].setFillColor(GameConstants::BLACKCELL_COLOR);
}
void View::HighlightPossibleMoves(const std::vector<coord_t>& possibleMoves)
{
    for (const auto& move: possibleMoves)
        HighlightCell(move, sf::Color::Green);
}
void View::RemoveHighlightPossibleMoves(const std::vector<coord_t>& possibleMoves)
{
    for (const auto& move: possibleMoves)
        RemoveHighlightCell(move);
}

void View::Render() const
{
    for (const auto& button : m_buttons)
    {
        if (button->m_isVisible)
            UpdateButtonState(button->m_button, button->m_isSelected, button->m_isHovered, button->m_wasHovered);
    }
}

void View::Launch()
{
    SetButtonPressed(GameContext::LAUNCHBUTTONID, true);

    m_buttons[GameContext::MENUBUTTONID]->m_button.setPosition(GameContext::MENUBUTTON_POSITION_LAUNCHED);
}

coord_t View::GetBoardCoordBase(const int x, const int y, const sf::Vector2f cellsize) const
{
    const auto i = static_cast<int>((y - GameConstants::BOARDOFFSET.y) / cellsize.y);
    const auto j = static_cast<int>((x - GameConstants::BOARDOFFSET.x) / cellsize.x);

    return std::make_pair(i, j);
}

void View::UpdateButtonSelectedFlag(const int buttonID, const bool newValue)
{
    m_buttons[buttonID]->m_isSelected = newValue;
}
void View::UpdateButtonHoveredFlag(const int buttonID, const bool newValue)
{
    m_buttons[buttonID]->m_isHovered = newValue;
}

void View::SetButtonVisibility(const int buttonID, const bool isVisible)
{
    m_buttons[buttonID]->m_isVisible = isVisible;
}
void View::SetButtonPressed(const int buttonID, const bool isPressed)
{
    m_buttons[buttonID]->m_isPressed = isPressed;
}

bool View::IsButtonSelected(const int buttonID) const
{
    return m_buttons[buttonID]->m_isSelected;
}
bool View::IsButtonPressed(const int buttonID) const
{
    return m_buttons[buttonID]->m_isPressed;
}
bool View::IsButtonVisible(const int buttonID) const
{
    return m_buttons[buttonID]->m_isVisible;
}

std::unique_ptr<Button>& View::GetButton(const int buttonID)
{
    return m_buttons[buttonID];
}

void View::NeedHighlight()
{
    m_flags.m_hasHighLightedCell = true;
}
void View::RemoveHighlight()
{
    m_flags.m_hasHighLightedCell = false;
}
bool View::HasHighLightedCell() const
{
    return m_flags.m_hasHighLightedCell;
}
