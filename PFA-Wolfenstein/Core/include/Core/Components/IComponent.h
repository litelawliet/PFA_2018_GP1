#pragma once
#include "Core/Tools/tinyxml2.h"

namespace Core::Components
{
	class IComponent
	{
	public:
		virtual ~IComponent() = default;
		virtual void Update(const double p_dt) = 0;
		// Serialize every components for tinyxml
		virtual tinyxml2::XMLElement* Serialize(tinyxml2::XMLDocument* p_document) = 0;
	};
}
