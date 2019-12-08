#pragma once
#include <Core/GameObject.h>

namespace Core::Components
{	
	enum class PLAYERSTATE
	{
		IS_JUMPING,
		ON_GROUND
	};

	class PlayerComponent : public IComponent
	{
	public:

		explicit PlayerComponent(Core::GameObject& p_gameObject);
		~PlayerComponent() = default;
		PlayerComponent(const PlayerComponent& p_other);

		int GetHealth() const;
		PLAYERSTATE GetState() const;

		void Move(const double p_dt) const;
		void Update(const double p_dt) override;
		tinyxml2::XMLElement* Serialize(tinyxml2::XMLDocument* p_document) override;
	private:
		int m_health;
		PLAYERSTATE m_state;
		Core::GameObject& m_gameObject;
	};
}

