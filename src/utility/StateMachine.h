#pragma once

#include <memory>

namespace hnd
{
    namespace util
    {
        template<class OwnerType>
        struct State
        {
            virtual void Enter(std::shared_ptr<OwnerType> owner) = 0;
            virtual void Execute(std::shared_ptr<OwnerType> owner) = 0;
            virtual void Exit(std::shared_ptr<OwnerType> owner) = 0;
        };

        template<class OwnerType>
        class StateMachine
        {
        public:

        private:
            std::shared_ptr<OwnerType> m_pOwner;
            std::shared_ptr<State<OwnerType>> m_pCurrentState;
            std::shared_ptr<State<OwnerType>> m_pPreviousState;
            std::shared_ptr<State<OwnerType>> m_pGlobalState;
        };
    }
}