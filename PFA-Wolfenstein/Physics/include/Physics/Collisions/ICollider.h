#pragma once
#include <stdafx.h>
#include <Physics/Export.h>
#include "Rendering/Resources/Transform.h"

namespace Physics::Collisions
{
	class API_PHYSICS ICollider
	{
	public:
		virtual ~ICollider() = default;
		virtual bool CollisionCheck(ICollider& p_other) = 0;

		//virtual Rendering::Resources::Transform& GetTransform() = 0;
		virtual std::vector<glm::vec3>& GetVertices() = 0;
		
		//virtual void SetTransform(Rendering::Resources::Transform& p_transform) = 0;

	protected:
		std::vector<glm::vec3> m_vertices;
	};
}
