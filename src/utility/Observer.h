#pragma once

#include <any>
#include <vector>
#include <algorithm>
#include <cstdint>
#include <string>

#include "Log.h"
#include "Defines.h"

namespace hnd
{
	namespace util
	{
		enum class EventType : uint16_t;

		struct Event
		{
			EventType type;
			std::any data;
		};

		class Observer
		{
		public:
			virtual ~Observer() = default;
			virtual void OnNotify(const Event& event) = 0;
		};

		class Subject
		{
		public:
			void AddObserver(Observer* obs)
			{
				observers.push_back(obs);
			}
			void RemoveObserver(Observer* obs)
			{
				observers.erase(std::find(observers.begin(), observers.end(), obs));
			}

		protected:
			void Notify(const Event& evt)
			{
				for (auto& obs : observers)
					obs->OnNotify(evt);
				HND_LOG_DEBUG("Notified with event type " + std::to_string(static_cast<uint16_t>(evt.type)));
			}

		private:
			std::vector<Observer*> observers;
		};

		enum class EventType : uint16_t
		{
			GUI_FROM_MAIN_TO_EDIT
		};
	}
}