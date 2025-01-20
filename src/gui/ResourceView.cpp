#include "ResourceView.h"

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
			int iter = 0;
			auto& pmgr = core::PackManager::GetInstance();
			auto& packs = core::PackManager::GetInstance().GetPackList();

			if (ImGui::Begin("Resources", 0, ImGuiWindowFlags_MenuBar))
			{
				if (ImGui::BeginMenuBar())
				{
					if (ImGui::BeginMenu("Manage"))
					{
						if (ImGui::MenuItem("Load All", NULL, false))
						{
							pmgr.LoadAll();
							LOG_F(INFO, "Loaded loaded resources");
						}
						if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
						{
							ImGui::SetTooltip("Uses the most memory but is faster");
						}

						if (ImGui::MenuItem("Pre-load All", NULL, false))
						{
							pmgr.PreLoadAll();
							LOG_F(INFO, "Pre-loaded loaded resources");
						}
						if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
						{
							ImGui::SetTooltip("Loads only names and pulls resources when needed. Recommended.");
						}

						if (ImGui::MenuItem("Unload All", NULL, false))
						{
							pmgr.ClearAll();
							LOG_F(INFO, "Cleared loaded resources");
						}
						if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
						{
							ImGui::SetTooltip("Clears all loaded resources");
						}

						ImGui::EndMenu();
					}

					ImGui::EndMenuBar();
				}

				if (ImGui::TreeNode("Packs"))
				{
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
					ImGui::TreePop();
				}
			}
			ImGui::End();
		}
	}
}