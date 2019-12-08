#include <memory>
#include <Physics/Collisions/ICollider.h>
#include <Physics/Collisions/BoxCollider.h>
#include <Core/Components/ColliderComponent.h>

Core::Components::ColliderComponent::ColliderComponent(GameObject & p_gameObject) : m_gameObject{ p_gameObject }
{
	Physics::Collisions::BoxCollider box(1.0f, 1.0f, 1.0f);
	m_gameObject.GetTransform().UpdateModelMatrix();

	for (auto& i : box.GetVertices())
	{
		i = glm::normalize(glm::mat3(m_gameObject.GetTransform().GetModelMatrix()) * i);
	}

	m_collider = std::make_shared<Physics::Collisions::BoxCollider>(box);
}

Core::Components::ColliderComponent::ColliderComponent(const ColliderComponent& p_other)
	: m_collider{ p_other.m_collider }, m_gameObject{ p_other.m_gameObject }
{
}

void Core::Components::ColliderComponent::MakeBoxCollider(float p_width, float p_height, float p_length)
{}

void Core::Components::ColliderComponent::Update(const double p_dt)
{
	std::shared_ptr<Physics::Collisions::BoxCollider> box = std::static_pointer_cast<Physics::Collisions::BoxCollider>(m_collider);
	m_gameObject.GetTransform().UpdateModelMatrix();
	//box->DrawCollisionBox();

	for (auto& i : m_collider->GetVertices())
	{
		i = glm::normalize(glm::mat3(m_gameObject.GetTransform().GetModelMatrix()) * i);
	}
}

tinyxml2::XMLElement* Core::Components::ColliderComponent::Serialize(tinyxml2::XMLDocument* p_document)
{
	tinyxml2::XMLElement * colliderElement = p_document->NewElement("Collider");
	const auto& colliderVertices = m_collider->GetVertices();

	for (const auto& vertex : colliderVertices)
	{
		tinyxml2::XMLElement * colliderPosition = p_document->NewElement("position");

		colliderPosition->SetAttribute("x", vertex.x);
		colliderPosition->SetAttribute("y", vertex.y);
		colliderPosition->SetAttribute("z", vertex.z);

		colliderElement->InsertEndChild(colliderPosition);
	}

	return colliderElement;
}

std::shared_ptr<Physics::Collisions::ICollider> Core::Components::ColliderComponent::GetCollider() const { return m_collider; }
