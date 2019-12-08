#pragma once
#include <Rendering/LowRenderer/Camera.h>
#include <Core/GameObject.h>

namespace Core::Components
{
	class CameraComponent : public IComponent
	{
	public:
		CameraComponent(Core::GameObject& p_gameObject, glm::vec3& p_distanceFromPlayer);
		~CameraComponent() = default;

		void Update(const double p_dt) override;

		tinyxml2::XMLElement* Serialize(tinyxml2::XMLDocument* p_document) override;

	private:
		Core::GameObject& m_gameObject;
		glm::vec3 m_distanceFromPlayer;
	};
}
