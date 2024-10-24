#pragma once

#include "raylib.h"

#include "../gui/Gui.h"
#include "Config.h"
#include "atlas/Map.h"

#include <exception>

namespace hnd
{
	namespace core
	{
		class App
		{
		public:
			void Init();
			void Run();

		private:
			void UpdateConfig() const;
		};
	}
}