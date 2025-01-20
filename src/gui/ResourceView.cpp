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
			}
			ImGui::End();
		}
	}
}