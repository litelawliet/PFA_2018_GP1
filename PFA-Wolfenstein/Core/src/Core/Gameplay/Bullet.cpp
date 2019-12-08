#include "Core/Gameplay/Bullet.h"


Core::Gameplay::Bullet::Bullet()
= default;

Core::Gameplay::Bullet::Bullet(glm::vec3 p_bulletDirection)
	: m_direction{ p_bulletDirection }, m_lifeTimeMaxDuration{ 5.0 }, m_lifeTime{ 0.0 }, m_toDestroy{ false }
{
}

Core::Gameplay::Bullet::~Bullet()
{
	std::cout << "Bullet destroyed\n";
}

void Core::Gameplay::Bullet::Update(const double p_dt)
{
	m_lifeTime += p_dt;
	if (m_lifeTime >= m_lifeTimeMaxDuration)
	{
		m_toDestroy = true;
	}

	glm::vec3 translation = glm::vec3{ m_direction.x * p_dt, m_direction.y * p_dt, m_direction.z * p_dt };
	m_bulletModel->TranslateBy(translation);
}

void Core::Gameplay::Bullet::SetDirection(const glm::vec3 & p_bulletDirection)
{
	m_direction = p_bulletDirection;
}

void Core::Gameplay::Bullet::SetBulletModel(std::shared_ptr<GameObject> p_model)
{
	m_bulletModel = p_model;
}

std::shared_ptr<Core::GameObject> Core::Gameplay::Bullet::GetBulletModel() const
{
	return m_bulletModel;
}

bool Core::Gameplay::Bullet::ToDestroy() const
{
	return m_toDestroy;
}
