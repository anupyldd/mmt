#pragma once

#include "GuiObject.h"
#include "../core/map/PackManager.h"
#include "../core/Localization.h"

#include "raylib.h"
#include "rlImGui.h"
#include "imgui.h"

#include <algorithm>

namespace mmt
{
	namespace core
	{
		class App;
	}

	namespace gui
	{
		class ResourceView : public GuiObject
		{
		public:
			ResourceView();
			virtual void Update(core::App* app) override final;

		private:
			std::string currentPack;			// pack of hovered resource
			std::vector<std::string> path;	
			std::vector<std::string> folders;	// temp folder structure
			core::ResourceType resType;			// type of resource hovere over, deduced from folder

		private:
			void ClearSelected(std::unordered_map<std::string, bool>& sel);


			template<class ResType>
			void IteratePackFolder(const core::PackFolder<ResType>& fold)
			{
				if (ImGui::TreeNode(fold.name.c_str()))
				{
					//if (!path.empty() && ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled)) 
					//	path.pop_back();
					//path.emplace_back(fold.name);
					//using namespace core;
					//if (fold.name == LocC("textures")) folders.emplace_back("textures");
					//else if (fold.name == LocC("objects")) folders.emplace_back("objects");
					//else if (fold.name == LocC("fonts")) folders.emplace_back("fonts");
					//else if (fold.name == LocC("scripts")) folders.emplace_back("scripts");
					//else folders.emplace_back(fold.name);
					folders.emplace_back(fold.name);

					for (const auto& r : fold.res)
					{
						if (ImGui::TreeNodeEx(r.first.c_str(), ImGuiTreeNodeFlags_Leaf | ImGuiTreeNodeFlags_Bullet))
						{
							if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
							{
								path.insert(path.end(), folders.begin(), folders.end());
								path.emplace_back(r.first);

								const auto& pr = core::PackManager::GetInstance().GetPreview(path);
								pr.Draw();
							}
							ImGui::TreePop();
						}
					}
					for (const auto& sf : fold.subFolders)
					{
						IteratePackFolder(*sf.second);
					}
					ImGui::TreePop();
				}
			}
		};
	}
}