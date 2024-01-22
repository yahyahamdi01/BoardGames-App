#pragma once

#include <stack>
#include <memory>

#include "State.hpp"

namespace Engine
{
    class StateManager
    {
        private:
            std::stack<std::unique_ptr<State>> m_stateS;
            std::unique_ptr<State> m_newState;

            bool m_add = false;
            bool m_replace = false;
            bool m_remove = false;
            bool m_removeAll = false;
        public:
            StateManager();
            ~StateManager();

            void Add(std::unique_ptr<State> toAdd, bool replace = false);
            void PopAll();
            void ProcessStateChange();
            
            std::unique_ptr<State>& GetCurrent();
            bool IsEmpty() const;
    };
}