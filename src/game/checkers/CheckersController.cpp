#include "../../../include/game/checkers/CheckersController.hpp"
#include "../../../include/GameChoice.hpp"

CheckersController::CheckersController(std::shared_ptr<Context> context): 
    Controller{context, std::make_unique<Checkers>(), std::make_unique<CheckersView>()}
{}

void CheckersController::HandleEvent(const sf::Event& event)
{
    Controller::HandleEvent(event);

    if (event.type == sf::Event::KeyPressed)
    {
        if (event.key.code == sf::Keyboard::A && !dynamic_cast<Checkers*>(m_model.get())->IsWhiteWantsDraw())
        {   
            dynamic_cast<Checkers*>(m_model.get())->SetWhiteWantsDraw(true);
            std::cout << "White wants draw" << std::endl;
        }
        else if (event.key.code == sf::Keyboard::P && !dynamic_cast<Checkers*>(m_model.get())->IsBlackWantsDraw())
        {
            dynamic_cast<Checkers*>(m_model.get())->SetBlackWantsDraw(true);
            std::cout << "Black wants draw" << std::endl;
        }
    }
}

void CheckersController::Update()
{
    Controller::Update();

    if (dynamic_cast<Checkers*>(m_model.get())->IsWhiteWantsDraw() 
    && dynamic_cast<Checkers*>(m_model.get())->IsBlackWantsDraw())
    {
        End();
    }

    if (m_model->IsCurrentPlayerChanged())
        ResetDraw();
}

void CheckersController::SetWindowTitle() const
{
    m_context->m_window->setTitle(WindowConstants::CHECKERS_TITLE);
}

void CheckersController::PrintAndResetPlayer() const
{
    m_view->PrintCurrentPlayer(m_model->GetCurrentPlayer());
    m_model->ResetCurrentPlayerChangedFlag();
}

void CheckersController::End() {
    m_view->PrintWinner(m_model->GetWinner());
    
    Controller::End();
}

void CheckersController::ResetDraw() const
{
    dynamic_cast<Checkers*>(m_model.get())->SetWhiteWantsDraw(false);
    dynamic_cast<Checkers*>(m_model.get())->SetBlackWantsDraw(false);
}



