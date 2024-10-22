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
                : owner(owner) { }

            void SetCurrentState(StatePtr newState) { currentState = newState; }
            void SetPreviousState(StatePtr newState) { previousState = newState; }
            void SetGlobalState(StatePtr newState) { globalState = newState; }

            void Update()
            {
                if (globalState) globalState->Execute(owner);
                if (currentState) currentState->Execute(owner);
            }

            void ChangeState(StatePtr newState)
            {
                if (!newState) INVALID_STATE_CHANGE_EXCEPTION_THROW(*this);

                previousState = currentState;
                currentState->Exit(owner);
                currentState = pNewState;
                currentState->Enter(owner);
            }

            void RevertToPreviousState()
            {
                ChangeState(previousState);
            }

            StatePtr GetCurrentState() const { return currentState; }
            StatePtr GetGlobalState() const { return globalState; }
            StatePtr GetPreviousState() const { return previousState; }

            bool IsInState(const State<OwnerType>& state) { return *currentState == state; }

        private:
            std::shared_ptr<OwnerType> owner;
            StatePtr currentState;
            StatePtr previousState;
            StatePtr globalState;
        };
    }
}

#define INVALID_STATE_CHANGE_EXCEPTION_THROW(fsm) {                     \
std::stringstream msg;                                                  \
msg << '[' << typeid(fsm).name() << ']' <<                              \
" Attempting to change to an invalid state.\n Last valid state: " <<    \
fsm.currentState;                                                       \
throw std::runtime_error(msg.str());                                    \
}