#pragma once
#include <Core/Components/IComponent.h>
#include <Physics/Collisions/ICollider.h>
#include <Physics/Collisions/BoxCollider.h>
#include <Core/GameObject.h>

namespace Core::Components
{
	class ColliderComponent : public IComponent
	{
	public:
		explicit ColliderComponent(GameObject& p_gameObject);
		~ColliderComponent() = default;
		ColliderComponent(const ColliderComponent& p_other);

		void MakeBoxCollider(float p_width, float p_height, float p_length);
		void Update(const double p_dt) override;
		tinyxml2::XMLElement* Serialize(tinyxml2::XMLDocument* p_document) override;
		std::shared_ptr<Physics::Collisions::ICollider> GetCollider() const;

	private:
		std::shared_ptr<Physics::Collisions::ICollider> m_collider;
		GameObject& m_gameObject;
	};
}
