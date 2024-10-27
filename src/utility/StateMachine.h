#pragma once

#include <memory>
#include <exception>
#include <string>

#define INVALID_STATE_CHANGE_EXCEPTION_THROW(fsm) {                     \
std::stringstream msg;                                                  \
msg << '[' << typeid(fsm).name() << ']' <<                              \
" Attempting to change to an invalid state.\n Last valid state: " <<    \
(fsm).currentState;                                                       \
throw std::runtime_error(msg.str());                                    \
}

namespace hnd
{
    namespace util
    {

        template<class OwnerType>
        struct State
        {
            State() = default;
            virtual void Enter(OwnerType* owner) = 0;
            virtual void Execute(OwnerType* owner) = 0;
            virtual void Exit(OwnerType* owner) = 0;
        };

        template<class OwnerType>
        struct EmptyState : public State<OwnerType>
        {
            virtual void Enter(OwnerType* owner) override final { };
            virtual void Execute(OwnerType* owner) override final { };
            virtual void Exit(OwnerType* owner) override final { };
        };

        // -----------------------

        template<class OwnerType>
        class StateMachine
        {
        public:
            StateMachine(OwnerType* owner)
                : owner(owner) { }

            void SetCurrentState(State<OwnerType>* newState) { currentState = newState; }
            void SetPreviousState(State<OwnerType>* newState) { previousState = newState; }
            void SetGlobalState(State<OwnerType>* newState) { globalState = newState; }

            void Update()
            {
                if (globalState) globalState->Execute(owner);
                if (currentState) currentState->Execute(owner);
            }

            void ChangeState(State<OwnerType>* newState)
            {
                if (!newState) INVALID_STATE_CHANGE_EXCEPTION_THROW(*this);

                previousState = currentState;
                currentState->Exit(owner);
                currentState = newState;
                currentState->Enter(owner);
            }

            void RevertToPreviousState()
            {
                ChangeState(previousState);
            }

            State<OwnerType>* GetCurrentState() const { return currentState; }
            State<OwnerType>* GetGlobalState() const { return globalState; }
            State<OwnerType>* GetPreviousState() const { return previousState; }

            bool IsInState(const State<OwnerType>& state) { return *currentState == state; }

        private:
            OwnerType* owner = nullptr;
            State<OwnerType>* currentState = nullptr;
            State<OwnerType>* previousState = nullptr;
            State<OwnerType>* globalState = nullptr;
        };
    }
}

