#define GLM_FORCE_SWIZZLE
#include <Core/Components/PlayerComponent.h>
#include <Core/GameObject.h>
#include <Rendering/Managers/InputManager.h>
#include "Rendering/LowRenderer/Camera.h"


Core::Components::PlayerComponent::PlayerComponent(Core::GameObject& p_gameObject) : m_gameObject{ p_gameObject }
{
	m_health = 100;
	m_state = PLAYERSTATE::IS_JUMPING;
}

Core::Components::PlayerComponent::PlayerComponent(const PlayerComponent & p_other) : m_gameObject{ p_other.m_gameObject }
{
	m_health = p_other.m_health;
	m_state = p_other.m_state;
}

int Core::Components::PlayerComponent::GetHealth() const
{
	return m_health;
}

Core::Components::PLAYERSTATE Core::Components::PlayerComponent::GetState() const
{
	return m_state;
}

void Core::Components::PlayerComponent::Move(const double p_dt) const
{
	Rendering::Managers::InputManager* inputManager = Rendering::Managers::InputManager::GetInstance().get();

	const auto dt_f = static_cast<float>(p_dt);

	if (Rendering::Managers::InputManager::GetInstance()->GetKey(Rendering::Utils::Event<int>::KeyCode::W))
	{
		glm::vec3 moveBy = Rendering::LowRenderer::Camera::GetInstance()->GetForward() *
			Rendering::LowRenderer::Camera::GetInstance()->GetMovementSpeed() * dt_f;
		m_gameObject.TranslateBy(moveBy);
		//m_weapon.GetWeaponModel()->TranslateBy(moveBy);
	}
	if (inputManager->GetKey(Rendering::Utils::Event<int>::KeyCode::S))
	{
		glm::vec3 moveBy = Rendering::LowRenderer::Camera::GetInstance()->GetBack() *
			Rendering::LowRenderer::Camera::GetInstance()->GetMovementSpeed() * dt_f;
		m_gameObject.TranslateBy(moveBy);
		//m_weapon.GetWeaponModel()->TranslateBy(moveBy);
	}
	if (inputManager->GetKey(Rendering::Utils::Event<int>::KeyCode::A))
	{
		glm::vec3 moveBy = -Rendering::LowRenderer::Camera::GetInstance()->GetRight() *
			Rendering::LowRenderer::Camera::GetInstance()->GetMovementSpeed() * dt_f;
		m_gameObject.TranslateBy(moveBy);
		//m_weapon.GetWeaponModel()->TranslateBy(moveBy);
	}
	if (inputManager->GetKey(Rendering::Utils::Event<int>::KeyCode::D))
	{
		glm::vec3 moveBy = Rendering::LowRenderer::Camera::GetInstance()->GetRight() *
			Rendering::LowRenderer::Camera::GetInstance()->GetMovementSpeed() * dt_f;
		m_gameObject.TranslateBy(moveBy);
		//m_weapon.GetWeaponModel()->TranslateBy(moveBy);
	}
}

void Core::Components::PlayerComponent::Update(const double p_dt)
{
	// glm::vec3 direction = Rendering::LowRenderer::Camera::GetInstance()->GetForward();
	glm::vec3 direction(0.0f, -Rendering::LowRenderer::Camera::GetInstance()->GetYaw() - 90, 0.0f);
	glm::vec3 finalDirection = direction + glm::vec3(0.0f, -90.0f, 0.0f);

	// Comment the line below to disable the Rotation of the 3D model
	// m_gameObject.GetTransform().SetRot(direction);
}

tinyxml2::XMLElement* Core::Components::PlayerComponent::Serialize(tinyxml2::XMLDocument* p_document)
{
	tinyxml2::XMLElement * player = p_document->NewElement("Player");

	player->SetAttribute("health", m_health);
	player->SetAttribute("playerState", static_cast<int>(m_state));

	return player;
}
