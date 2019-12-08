#pragma once
#include <glm/vec3.hpp>
#include "Core/GameObject.h"

namespace Core::Gameplay
{
	class Bullet
	{
	public:
		Bullet();
		Bullet(glm::vec3 p_bulletDirection);
		~Bullet();

		void Update(const double p_dt);

		void SetDirection(const glm::vec3 & p_bulletDirection);
		void SetBulletModel(std::shared_ptr<GameObject> p_model);

		std::shared_ptr<GameObject> GetBulletModel() const;

		// In gameManager, check if the bullets need to be destroyed or not using the GetBulletsList from weapon. Pop the object if true
		bool ToDestroy() const;

	private:
		std::shared_ptr<Core::GameObject> m_bulletModel;
		glm::vec3 m_direction{};
		double m_lifeTimeMaxDuration{};
		double m_lifeTime{};
		bool m_toDestroy{};
	};
}
