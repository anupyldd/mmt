#include "ResourceView.h"
#include "../core/Localization.h"

#include <vector>
#include <algorithm>

namespace mmt
{
	namespace gui
	{
		ResourceView::ResourceView()
		{
		}

		int selected = -1;
		void ResourceView::Update(core::App* app)
		{
			using namespace core;

			int iter = 0;
			auto& pmgr = core::PackManager::GetInstance();
			auto& packs = core::PackManager::GetInstance().GetPackList();

			//if (ImGui::Begin(LocC("resources"), 0, ImGuiWindowFlags_MenuBar))
			if (ImGui::Begin((const char*)u8"אבגדהִ", 0, ImGuiWindowFlags_MenuBar))
			{
				if (ImGui::BeginMenuBar())
				{
					if (ImGui::BeginMenu(LocC("manage")))
					{
						if (ImGui::MenuItem(LocC("load_all"), NULL, false))
						{
							pmgr.LoadAll();
							LOG_F(INFO, "Loaded resources");
						}
						if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
						{
							ImGui::SetTooltip(LocC("load_all_tt"));
						}

						if (ImGui::MenuItem(LocC("scan_all"), NULL, false))
						{
							pmgr.PreLoadAll();
							LOG_F(INFO, "Pre-loaded resources");
						}
						if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
						{
							ImGui::SetTooltip(LocC("scan_all_tt"));
						}

						if (ImGui::MenuItem(LocC("clear_all"), NULL, false))
						{
							pmgr.ClearAll();
							LOG_F(INFO, "Cleared loaded resources");
						}
						if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
						{
							ImGui::SetTooltip(LocC("clear_all_tt"));
						}

						ImGui::EndMenu();
					}

					ImGui::EndMenuBar();
				}

				// -----------------------------------------

				//if (ImGui::TreeNode("Packs"))
				//{
					for (const auto& pack : packs)
					{
						if (ImGui::TreeNode(pack.first.c_str()))
						{
							IteratePackFolder(pack.second.GetTextureFolder());
							IteratePackFolder(pack.second.GetObjectFolder());
							IteratePackFolder(pack.second.GetFontFolder());
							ImGui::TreePop();
						}
					}
				//	ImGui::TreePop();
				//}
			}
			ImGui::End();
		}
	}
}