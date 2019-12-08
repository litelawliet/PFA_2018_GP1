#pragma once
#include <Core/GameObject.h>
#include <list>
#include "Core/Gameplay/Bullet.h"
#include <Audio/AudioClip.h>

namespace Core::Components
{	
	constexpr unsigned int MAX_BULLETS = 50;
	class WeaponComponent : public IComponent
	{
	public:

		WeaponComponent(Core::GameObject& p_gameObject, std::shared_ptr<GameObject> p_weapon);
		~WeaponComponent() = default;
		void SetWeaponModel(std::shared_ptr<GameObject> p_model);
		WeaponComponent(const WeaponComponent& p_other);

		void SetBulletModel(std::shared_ptr<GameObject> p_model);

		void Update(const double p_dt) override;
		tinyxml2::XMLElement* Serialize(tinyxml2::XMLDocument* p_document) override;
		void Shoot();

		// Please hold a reference of it for performance when calling this function
		std::list<std::unique_ptr<Gameplay::Bullet>>& GetBulletsList() noexcept;
		const std::shared_ptr<Core::GameObject>&  GetWeaponModel() const;


	private:
		Core::GameObject& m_gameObject;
		std::shared_ptr<GameObject> m_weaponObject;

		std::list<std::unique_ptr<Gameplay::Bullet>> m_bullets;
		std::list<std::list<std::unique_ptr<Gameplay::Bullet>>::iterator> m_listOfBulletToDestroy;
		Audio::AudioClip m_gunshotClip;

	protected:
		std::shared_ptr<GameObject> m_bulletModel;
	};
}
