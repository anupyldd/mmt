#include "Layer.h"

namespace hnd
{
	namespace core
	{
		void Layer::AddObject(const MapObject& obj)
		{
			if (!objectTree.InsertObject(obj))
				LOG_ERROR("Failed to insert object: " + std::to_string(obj.id)); 
		}
	}
}