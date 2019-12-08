#pragma once
#include <Physics/Export.h>
#include <stdafx.h>
#include <Physics/Collisions/ICollider.h>

namespace Physics::Collisions
{
	class API_PHYSICS BoxCollider : public ICollider
	{
	public:
		BoxCollider(float p_width, float p_height, float p_length);
		~BoxCollider() = default;
		BoxCollider(const BoxCollider& p_other);

		void DrawCollisionBox();
		bool CollisionCheck(ICollider& p_other) override;

		//Rendering::Resources::Transform& GetTransform() override;
		std::vector<glm::vec3>& GetVertices() override;

		//void SetTransform(Rendering::Resources::Transform& p_transform) override;
	};
}
