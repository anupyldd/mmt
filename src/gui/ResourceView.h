#pragma once

#include "GuiObject.h"
#include "../core/map/PackManager.h"

#include "raylib.h"
#include "rlImGui.h"
#include "imgui.h"

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
			template<class ResType>
			void IteratePackFolder(const core::PackFolder<ResType>& fold)
			{
				if (ImGui::TreeNode(fold.name.c_str()))
				{
					for (const auto& r : fold.res)
					{
						if (ImGui::TreeNodeEx(r.first.c_str(), ImGuiTreeNodeFlags_Leaf | ImGuiTreeNodeFlags_Bullet))
							ImGui::TreePop();
					}
					for (const auto& sf : fold.subFolders)
					{
						if (ImGui::TreeNode(sf.first.c_str()))
						{
							IteratePackFolder(*sf.second);
							ImGui::TreePop();
						}
					}
					ImGui::TreePop();
				}
				/*
				if (ImGui::BeginListBox(fold.name.c_str(), ImGui::GetContentRegionAvail()))
				{
					//DLOG_F(WARNING, "Open LB %s", fold.name.c_str());

					for (const auto& r : fold.res)
					{
						ImGui::Selectable(r.first.c_str(), false, 0, ImGui::GetItemRectSize());
						//DLOG_F(WARNING, "Add Item %s", r.first.c_str());
					}
					for (const auto& sf : fold.subFolders)
					{
						if (ImGui::BeginListBox(sf.first.c_str(), ImGui::GetContentRegionAvail()))
						{
							//DLOG_F(WARNING, "Open LB %s", sf.first.c_str());
							IteratePackFolder(*sf.second);
							ImGui::EndListBox();
							//DLOG_F(WARNING, "Close LB %s", sf.first.c_str());
						}
					}
					ImGui::EndListBox();
					//DLOG_F(WARNING, "Close LB %s", fold.name.c_str());
				}
				*/
			}
		};
	}
}