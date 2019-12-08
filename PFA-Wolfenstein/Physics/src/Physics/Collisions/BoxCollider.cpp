#include <stdafx.h>
#include <Physics/Collisions/BoxCollider.h>

Physics::Collisions::BoxCollider::BoxCollider(float p_width, float p_height, float p_length)
{
	//front face
	m_vertices.emplace_back(glm::vec3(-p_width / 2, p_height / 2, p_length / 2));
	m_vertices.emplace_back(glm::vec3(p_width / 2, p_height / 2, p_length / 2));
	m_vertices.emplace_back(glm::vec3(p_width / 2, -p_height / 2, p_length / 2));
	m_vertices.emplace_back(glm::vec3(-p_width / 2, -p_height / 2, p_length / 2) );

	//back face
	m_vertices.emplace_back(glm::vec3(-p_width / 2, p_height / 2, -p_length / 2));
	m_vertices.emplace_back(glm::vec3(p_width / 2, p_height / 2, -p_length / 2));
	m_vertices.emplace_back(glm::vec3(p_width / 2, -p_height / 2, -p_length / 2));
	m_vertices.emplace_back(glm::vec3(-p_width / 2, -p_height / 2, -p_length / 2));
}

Physics::Collisions::BoxCollider::BoxCollider(const BoxCollider & p_other)
{
	for (auto& vertex : p_other.m_vertices)
	{
		m_vertices.emplace_back(vertex);
	}
}

void Physics::Collisions::BoxCollider::DrawCollisionBox()
{
	glLineWidth(2.0f);
	glBegin(GL_LINES);

	for (auto& vertex : m_vertices)
	{
		glVertex3f(vertex.x, vertex.y, vertex.z);
	}

	glEnd();

	std::cout << "\n-------------------\n";

	for (auto& vertex : m_vertices)
		std::cout << vertex.x << ", " << vertex.y << ", " << vertex.z << '\n';

	std::cout << "-------------------\n";
}

bool Physics::Collisions::BoxCollider::CollisionCheck(ICollider & p_other)
{
	return false;
}

//Rendering::Resources::Transform& Physics::Collisions::BoxCollider::GetTransform() { return m_transform; }

std::vector<glm::vec3>& Physics::Collisions::BoxCollider::GetVertices() { return m_vertices; }

//void Physics::Collisions::BoxCollider::SetTransform(Rendering::Resources::Transform & p_transform) { m_transform = p_transform; }
