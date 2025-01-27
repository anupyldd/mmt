#include "ResourceView.h"
#include "../core/Localization.h"

#include <vector>
#include <algorithm>
#include <sstream>

namespace mmt
{
	namespace gui
	{
		std::unordered_map<std::string, bool> selectedPacks;
			
		// -------------------------

		ResourceView::ResourceView()
		{
			folders.reserve(10);
		}

		int selected = -1;
		void ResourceView::Update(core::App* app)
		{
			using namespace core;

			int iter = 0;
			auto& pmgr = core::PackManager::GetInstance();
			auto& packs = core::PackManager::GetInstance().GetPackList();

			if (ImGui::Begin(LocC("resources"), 0, ImGuiWindowFlags_MenuBar))
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

						ImGui::Separator();	// ---------------------------------------

						if (ImGui::MenuItem(LocC("load_sel"), NULL, false))
						{
							pmgr.LoadSelected(selectedPacks);
							ClearSelected(selectedPacks);
							LOG_F(INFO, "Loaded selected resources");
						}
						if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
						{
							ImGui::SetTooltip(LocC("load_sel_tt"));
						}

						if (ImGui::MenuItem(LocC("scan_sel"), NULL, false))
						{
							pmgr.PreLoadSelected(selectedPacks);
							ClearSelected(selectedPacks);
							LOG_F(INFO, "Scanned selected resources");
						}
						if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
						{
							ImGui::SetTooltip(LocC("scan_sel_tt"));
						}

						ImGui::Separator();	// ---------------------------------------

						if (ImGui::MenuItem(LocC("clear_all"), NULL, false))
						{
							pmgr.ClearAll();
							pmgr.FindAvailable();
							LOG_F(INFO, "Cleared loaded resources");
						}
						if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
						{
							ImGui::SetTooltip(LocC("clear_all_tt"));
						}

						// doesn't really work with current setup
						// since loaded packs cannot be selected
						// TODO
						//if (ImGui::MenuItem(LocC("clear_sel"), NULL, false))
						//{
						//	pmgr.ClearSelected(selectedPacks);
						//	ClearSelected(selectedPacks);
						//	LOG_F(INFO, "Cleared selected resources");
						//}
						//if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
						//{
						//	ImGui::SetTooltip(LocC("clear_sel_tt"));
						//}

						ImGui::EndMenu();
					}

					ImGui::EndMenuBar();
				}

				// -----------------------------------------

				path.clear();
				folders.clear();

				for (const auto& pack : packs)
				{
					if (pack.second.GetState() != PackState::Unloaded)
					{
						if (ImGui::TreeNode(pack.first.c_str()))
						{
							path.emplace_back(pack.first);

							IteratePackFolder(pack.second.GetTextureFolder());
							folders.clear();
							IteratePackFolder(pack.second.GetObjectFolder());
							folders.clear();
							IteratePackFolder(pack.second.GetFontFolder());
							folders.clear();

							ImGui::TreePop();
						}
					}
					else
					{
						if (!selectedPacks.contains(pack.first)) 
							selectedPacks[pack.first] = false;

						if (ImGui::Checkbox(pack.first.c_str(), &selectedPacks.at(pack.first)))
						{

						}
					}
				}

				// shows path for debugging
				if (ImGui::BeginMenuBar())
				{
					std::stringstream sstr;
					for (const auto& p : path) sstr << p << '/';
					ImGui::Text("%s", sstr.str().c_str());
					ImGui::EndMenuBar();
				}
			}
			ImGui::End();
		}
		void ResourceView::ClearSelected(std::unordered_map<std::string, bool>& sel)
		{
			for (auto& [f, s] : sel)
			{
				if (s) s = false;
			}
		}
	}
}