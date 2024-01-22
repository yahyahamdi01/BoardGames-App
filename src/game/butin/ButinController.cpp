#include "../../../include/game/butin/ButinController.hpp"
#include "../../../include/GameChoice.hpp"

ButinController::ButinController(std::shared_ptr<Context> context): 
    Controller{context, std::make_unique<Butin>(), std::make_unique<ButinView>()}
{}

void ButinController::SetWindowTitle() const
{
    m_context->m_window->setTitle(WindowConstants::BUTIN_TITLE);
}

void ButinController::HandleEvent(const sf::Event& event)
{
    Controller::HandleEvent(event);

    if (event.type == sf::Event::KeyPressed)
    {
        bool firstRound{dynamic_cast<Butin*>(m_model.get())->IsFirstRound()};
        if (!firstRound && event.key.code == sf::Keyboard::Space)
        {
            dynamic_cast<Butin*>(m_model.get())->SwitchPlayer();
            dynamic_cast<Butin*>(m_model.get())->DeselectPiece();
            dynamic_cast<Butin*>(m_model.get())->ResetReplayFlag();
        }
    }
}

void ButinController::PrintAndResetPlayer() const
{
    dynamic_cast<ButinView*>(m_view.get())->PrintTurn(m_model->GetCurrentPlayer(), m_model->GetPlayers());
    m_model->ResetCurrentPlayerChangedFlag();
}

void ButinController::End() 
{
    m_view->PrintWinner(m_model->GetWinner());
    dynamic_cast<ButinView*>(
        m_view.get())->PrintScore(dynamic_cast<Butin*>(m_model.get())->GetWinnerScore()
    );
    
    Controller::End();
}
