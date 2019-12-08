#include <Core/Components/WeaponComponent.h>
#include <Core/GameObject.h>
#include <Rendering/Managers/InputManager.h>
#include <Rendering/LowRenderer/Camera.h>
#include <Core/Gameplay/Bullet.h>
#include <utility>
#include "Core/GameManager.h"


Core::Components::WeaponComponent::WeaponComponent(Core::GameObject& p_gameObject, std::shared_ptr<GameObject> p_weapon)
	: m_gameObject{ p_gameObject }, m_weaponObject{ std::move(p_weapon) }
{
}

void Core::Components::WeaponComponent::SetWeaponModel(std::shared_ptr<GameObject> p_model)
{
	m_weaponObject = p_model;
}

Core::Components::WeaponComponent::WeaponComponent(const WeaponComponent & p_other) :
	m_gameObject{ p_other.m_gameObject }, m_weaponObject{ p_other.m_weaponObject }
{
}

void Core::Components::WeaponComponent::SetBulletModel(std::shared_ptr<GameObject> p_model)
{
	m_bulletModel = p_model;
}

void Core::Components::WeaponComponent::Update(const double p_dt)
{
	//glm::vec3 direction = Rendering::LowRenderer::Camera::GetInstance()->GetForward();
	const glm::vec3 direction(0.0f, -Rendering::LowRenderer::Camera::GetInstance()->GetYaw() - 90, 0.0f);
	glm::vec3 finalDirection = direction + glm::vec3(0.0f, -90.0f, 0.0f);

	// TODO : Problem accessing the shared model
	// Here we rotate the WeaponModel
	/*Rendering::Resources::Transform newTransform = m_bulletModel->GetTransform();
	newTransform.SetRot(direction);
	m_bulletModel->SetTransform(newTransform);*/
	// 	m_bulletModel->GetTransform().SetRot(direction);

	if (!m_bullets.empty())
	{
		for (auto bullet = m_bullets.begin(); bullet != m_bullets.end(); ++bullet)
		{
			(*bullet)->Update(p_dt);
			if ((*bullet)->ToDestroy())
			{
				// Remove gameObject from ActiveScene
				//GameManager::GetActiveScene()->RemoveGameObject((*bullet)->GetBulletModel());
				m_listOfBulletToDestroy.push_back(bullet);
			}
		}

		for (const auto& bulletToDestroy : m_listOfBulletToDestroy)
		{
			m_bullets.erase(bulletToDestroy);
		}
		m_listOfBulletToDestroy.clear();
	}
}

tinyxml2::XMLElement* Core::Components::WeaponComponent::Serialize(tinyxml2::XMLDocument* p_document)
{
	return nullptr;
}

void Core::Components::WeaponComponent::Shoot()
{
	if (m_bullets.size() <= MAX_BULLETS)
	{
		m_bullets.push_back(std::make_unique<Gameplay::Bullet>(Rendering::LowRenderer::Camera::GetInstance()->GetForward()));
		m_bullets.back()->SetBulletModel(m_bulletModel); // TODO: Make new objects based on this model instead of reference

		m_bullets.back()->GetBulletModel()->SetTransform(m_weaponObject->GetTransform());
		glm::vec3 rotationBullet = glm::vec3(-90.0f, 0.0f, 0.0f);
		m_bullets.back()->GetBulletModel()->GetTransform().SetRot(rotationBullet);
		m_bullets.back()->SetDirection(Rendering::LowRenderer::Camera::GetInstance()->GetForward());

		GameManager::GetActiveScene()->AddGameObject(m_bullets.back()->GetBulletModel(), "bullet" + std::to_string(m_bullets.size()));
		m_gunshotClip.Play2DClip("../rsc/audio/fx/9mm_gunshot.wav");
		std::cout << "Bullet #" << m_bullets.size() << " instantiated.\n";
	}
	else
	{
		std::cerr << "Max bullets count reached.\n";
	}
}

std::list<std::unique_ptr<Core::Gameplay::Bullet>>& Core::Components::WeaponComponent::GetBulletsList() noexcept
{
	return m_bullets;
}

const std::shared_ptr<Core::GameObject>& Core::Components::WeaponComponent::GetWeaponModel() const
{
	return m_weaponObject;
}
