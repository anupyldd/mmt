#include "ResourceView.h"

#include <vector>
#include <algorithm>

namespace mmt
{
	namespace gui
	{
		ResourceView::ResourceView()
			//: select(core::PackManager::GetInstance().GetPackList().size(), false)
		{
		}

		int selected = -1;
		void ResourceView::Update(core::App* app)
		{
			int iter = 0;
			auto& packs = core::PackManager::GetInstance().GetPackList();

			if (ImGui::Begin("Resources", 0, 0))
			{
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
				/*
				if (ImGui::BeginListBox("Packs", ImGui::GetWindowSize()))
				{

					for (const auto& pack : packs)
					{
						bool isSelected = (selected == iter);
						//if (ImGui::Selectable(pack.first.c_str(), isSelected, 0, ImGui::GetItemRectSize()))
						//{
						//	selected = iter;
						//}

						// begin pack
						if (ImGui::BeginListBox(pack.first.c_str(), ImGui::GetItemRectSize()))
						{
							const auto& tex = pack.second.GetTextureFolder();
							const auto& obj = pack.second.GetObjectFolder();
							const auto& fnt = pack.second.GetFontFolder();

							IteratePackFolder(tex);
							IteratePackFolder(obj);
							IteratePackFolder(fnt);

							++iter;
						}
						// end pack	
						ImGui::EndListBox();
					}
				}
				ImGui::EndListBox();
				*/
			}
			ImGui::End();
		}
	}
}