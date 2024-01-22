#include "../../../include/game/bulltricker/BulltrickerController.hpp"

BulltrickerController::BulltrickerController(std::shared_ptr<Context> context):
    Controller{context, std::make_unique<Bulltricker>(), std::make_unique<BulltrickerView>()}
{}

void BulltrickerController::Update()
{
    Controller::Update();
}

void BulltrickerController::SetWindowTitle() const
{
    m_context->m_window->setTitle(WindowConstants::BULLTRICKER_TITLE);
}

void BulltrickerController::PrintAndResetPlayer() const
{
    dynamic_cast<BulltrickerView*>(m_view.get())->PrintCurrentPlayer(m_model->GetCurrentPlayer());
    m_model->ResetCurrentPlayerChangedFlag();
}

void BulltrickerController::End() 
{
    m_view->PrintWinner(m_model->GetWinner());
    Controller::End();
}