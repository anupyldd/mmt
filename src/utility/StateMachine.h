#pragma once

#include <memory>
#include <exception>
#include <string>

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
        struct EmptyState : public State<OwnerType>
        {
            virtual void Enter(std::shared_ptr<OwnerType> owner) override final { };
            virtual void Execute(std::shared_ptr<OwnerType> owner) override final { };
            virtual void Exit(std::shared_ptr<OwnerType> owner) override final { };
        };

        // -----------------------

        template<class OwnerType>
        class StateMachine
        {
            using StatePtr = std::shared_ptr<State<OwnerType>>;

        public:
            StateMachine(std::shared_ptr<OwnerType> owner)
                : m_pOwner(owner) { }

            void SetCurrentState(StatePtr newState) { m_pCurrentState = newState; }
            void SetPreviousState(StatePtr newState) { m_pPreviousState = newState; }
            void SetGlobalState(StatePtr newState) { m_pGlobalState = newState; }

            void Update()
            {
                if (m_pGlobalState) m_pGlobalState->Execute(m_pOwner);
                if (m_pCurrentState) m_pCurrentState->Execute(m_pOwner);
            }

            void ChangeState(StatePtr newState)
            {
                if (!newState) INVALID_STATE_CHANGE_EXCEPTION_THROW(*this);

                m_pPreviousState = m_pCurrentState;
                m_pCurrentState->Exit(m_pOwner);
                m_pCurrentState = pNewState;
                m_pCurrentState->Enter(m_pOwner);
            }

            void RevertToPreviousState()
            {
                ChangeState(m_pPreviousState);
            }

            StatePtr GetCurrentState() const { return m_pCurrentState; }
            StatePtr GetGlobalState() const { return m_pGlobalState; }
            StatePtr GetPreviousState() const { return m_pPreviousState; }

            bool IsInState(const State<OwnerType>& state) { return *m_pCurrentState == state; }

        private:
            std::shared_ptr<OwnerType> m_pOwner;
            StatePtr m_pCurrentState;
            StatePtr m_pPreviousState;
            StatePtr m_pGlobalState;
        };
    }
}

#define INVALID_STATE_CHANGE_EXCEPTION_THROW(fsm) {                     \
std::stringstream msg;                                                  \
msg << '[' << typeid(fsm).name() << ']' <<                              \
" Attempting to change to an invalid state.\n Last valid state: " <<    \
fsm.m_pCurrentState;                                                    \
throw std::runtime_error(msg.str());                                    \
}