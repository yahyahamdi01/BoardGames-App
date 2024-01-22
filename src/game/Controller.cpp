#include "../../include/game/Controller.hpp"
#include "../../include/GameChoice.hpp"
#include "../../include/Constants.hpp"

using namespace UIConstants::GameContext;

Controller::Controller(std::shared_ptr<Context> context, std::unique_ptr<Model> model, std::unique_ptr<View> view): 
    m_context{context},
    m_model{std::move(model)},
    m_view{std::move(view)}
{}

void Controller::Init()
{
    SetWindowTitle();

    m_model->Init();
    m_view->Init(m_context, *m_model->GetBoard());
}

void Controller::ProcessInput()
{
    sf::Event event;

    while (m_context->m_window->pollEvent(event))
    {
        HandleEvent(event);
    }
}
void Controller::HandleEvent(const sf::Event& event)
{
    if (event.type == sf::Event::Closed)
    {
        CloseWindow();
    }

    HandleMouseEvent(event);
}
void Controller::HandleMouseEvent(const sf::Event& event)
{
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

void Controller::Update()
{
    m_view->Render();

    UpdateHighlight();
    UpdateBoard();
    UpdateCurrentPlayer();
    UpdateButtonPushed();  
}
void Controller::UpdateHighlight() const
{
    if (m_model->IsPieceSelected() && !m_view->HasHighLightedCell())
        HighlightSelectedPiece();
    else if (HavePieceChanged())
        RemoveHighlightSelectedPiece();
}
void Controller::UpdateBoard() const
{
    if (m_model->IsBoardNeedUpdate())
    {
        m_view->UpdateBoard(*m_model->GetBoard());
        m_model->ResetBoardNeedUpdateFlag();
    }
}
void Controller::UpdateCurrentPlayer() const
{
    if (m_model->IsCurrentPlayerChanged() && !m_model->IsGameFinished())
    {
        PrintAndResetPlayer();
    }
}
void Controller::UpdateButtonPushed()
{
    if (m_view->IsButtonPressed(LAUNCHBUTTONID)) Start();

    if (m_view->IsButtonPressed(MENUBUTTONID)) End();
}

void Controller::HighlightSelectedPiece() const
{
    const auto& selectedPiece = m_model->GetSelectedPiece();
    const auto& possibleMoves = m_model->GetPossibleMoves(selectedPiece);

    m_view->HighlightCell(selectedPiece, sf::Color::Magenta);
    m_view->HighlightPossibleMoves(possibleMoves);
    m_view->NeedHighlight();
}
void Controller::RemoveHighlightSelectedPiece() const
{
    const auto& lastSelectedPiece = m_model->GetLastSelectedPiece();
    const auto& lastPossibleMoves = m_model->GetLastPossibleMoves();
    
    m_view->RemoveHighlightCell(lastSelectedPiece);
    m_view->RemoveHighlightPossibleMoves(lastPossibleMoves);
    m_model->ResetSelectedPieceFlag();
    m_view->RemoveHighlight();
}

void Controller::Draw()
{
    m_view->Draw(*m_context->m_window);
}

void Controller::UpdateButtonHoverState(const sf::Event& event)
{
    bool isMenuHovered = IsButtonHovered(m_view->GetButton(MENUBUTTONID)->m_button, event);
    bool isLaunchgameHovered = IsButtonHovered(m_view->GetButton(LAUNCHBUTTONID)->m_button, event);

    m_view->UpdateButtonHoveredFlag(MENUBUTTONID, isMenuHovered);
    m_view->UpdateButtonHoveredFlag(LAUNCHBUTTONID, isLaunchgameHovered);
}
void Controller::UpdateButtonSelectionState() {
    bool isMenuSelected = IsButtonSelected(m_view->GetButton(MENUBUTTONID)->m_button, *m_context->m_window);
    bool isLaunchgameSelected = IsButtonSelected(m_view->GetButton(LAUNCHBUTTONID)->m_button, *m_context->m_window);

    m_view->UpdateButtonSelectedFlag(MENUBUTTONID, isMenuSelected);
    m_view->UpdateButtonSelectedFlag(LAUNCHBUTTONID, isLaunchgameSelected);
}
void Controller::HandleMousePressed(const sf::Event& event) {
    bool isMousePressed = event.mouseButton.button == sf::Mouse::Left;

    if (isMousePressed)
    {
        if (m_view->IsButtonSelected(LAUNCHBUTTONID))
            m_view->GetButton(LAUNCHBUTTONID)->m_action();
        if (m_view->IsButtonSelected(MENUBUTTONID))
            m_view->GetButton(MENUBUTTONID)->m_action();
        if (m_model->IsGameStarted())
        {
            auto x = event.mouseButton.x;
            auto y = event.mouseButton.y;

            using namespace GameConstants;
            if (x < CLICKABLE_ZONE.first || x > CLICKABLE_ZONE.second || y < CLICKABLE_ZONE.first || y > CLICKABLE_ZONE.second)
                return;

            std::pair<int, int> coord = m_view->GetBoardCoord(x, y);
            
            m_model->Turn(coord);
        }
        if (m_model->IsGameFinished())
        {
            End();
        }

    }
}

void Controller::Start()
{
    m_view->SetButtonVisibility(LAUNCHBUTTONID, false);
    m_model->GameStart();
    m_view->PrintCurrentPlayer(m_model->GetCurrentPlayer());
    m_view->SetButtonPressed(LAUNCHBUTTONID, false);
}

void Controller::End()
{
    CloseGame();
}

bool Controller::HavePieceChanged() const
{
    return m_model->IsSelectedPieceChanged() 
        && m_model->GetLastSelectedPiece().first != -1
        && m_model->GetLastSelectedPiece().second != -1
        && m_model->GetLastSelectedPiece() != m_model->GetSelectedPiece();
}

void Controller::CloseWindow() const
{
    m_context->m_states->PopAll();
    m_context->m_window->close();
}
void Controller::CloseGame() const
{
    m_context->m_states->Add(std::make_unique<GameChoice>(m_context), true);
}