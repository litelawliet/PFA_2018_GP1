#include <stdafx.h>
#include <Rendering/Resources/Mesh.h>

Rendering::Resources::Mesh::Mesh(const std::vector<Geometry::Vertex>& p_vertices, const std::vector<uint32_t>& p_indices) noexcept
	: m_vertexCount{ static_cast<uint32_t>(p_vertices.size()) }, m_indicesCount{ static_cast<uint32_t>(p_indices.size()) }
{
	m_vertexArray = std::make_unique<Buffers::VertexArray>();
	m_texture = std::make_shared<Texture>();
	m_normalMap = std::make_shared<Texture>();
	CreateBuffers(p_vertices, p_indices);
}

void Rendering::Resources::Mesh::AddTexture(const std::string& p_texturePath) const
{
	m_texture->Load(p_texturePath, 1);
}

void Rendering::Resources::Mesh::AddNormalMap(const std::string& p_texturePath) const
{
	m_normalMap->Load(p_texturePath, 2);
}

void Rendering::Resources::Mesh::Bind() const noexcept
{
	m_vertexArray->Bind();
	m_indexBuffer->Bind();
}

void Rendering::Resources::Mesh::BindTextures() const noexcept
{
	m_texture->Bind(0);
	m_normalMap->Bind(1);
}

void Rendering::Resources::Mesh::Unbind() const noexcept
{

	m_indexBuffer->Unbind();
	m_vertexArray->Unbind();
}

void Rendering::Resources::Mesh::UnbindTextures() const noexcept
{
	m_normalMap->Unbind();
	m_texture->Unbind();
}

uint32_t Rendering::Resources::Mesh::GetVertexCount() const noexcept
{
	return m_vertexCount;
}

uint32_t Rendering::Resources::Mesh::GetIndicesCount() const noexcept
{
	return m_indicesCount;
}

void Rendering::Resources::Mesh::CreateBuffers(const std::vector<Geometry::Vertex>& p_vertices,
	const std::vector<uint32_t>& p_indices) noexcept
{
	m_vertexArray->Bind();

	std::vector<float> rawPositions{};
	std::vector<float> rawTextCoords{};
	std::vector<float> rawNormals{};
	std::vector<float> rawTangents{};
	std::vector<float> rawBitangents{};

	for (const auto& vertex : p_vertices)
	{
		// Position
		rawPositions.push_back(vertex.m_position[0]);
		rawPositions.push_back(vertex.m_position[1]);
		rawPositions.push_back(vertex.m_position[2]);

		// TextCoord
		rawTextCoords.push_back(vertex.m_textCoords[0]);
		rawTextCoords.push_back(vertex.m_textCoords[1]);

		// Normal
		rawNormals.push_back(vertex.m_normal[0]);
		rawNormals.push_back(vertex.m_normal[1]);
		rawNormals.push_back(vertex.m_normal[2]);

		rawTangents.push_back(vertex.m_tangent[0]);
		rawTangents.push_back(vertex.m_tangent[1]);
		rawTangents.push_back(vertex.m_tangent[2]);

		rawBitangents.push_back(vertex.m_tangent[0]);
		rawBitangents.push_back(vertex.m_tangent[1]);
		rawBitangents.push_back(vertex.m_tangent[2]);
	}

	// Buffer gen
	m_vboPosition = std::make_unique<Buffers::VertexBuffer>(rawPositions);
	m_vboTextCoords = std::make_unique<Buffers::VertexBuffer>(rawTextCoords);
	m_vboNormal = std::make_unique<Buffers::VertexBuffer>(rawNormals);
	m_vboTangent = std::make_unique<Buffers::VertexBuffer>(rawTangents);
	m_vboBitangent = std::make_unique<Buffers::VertexBuffer>(rawBitangents);

	m_indexBuffer = std::make_unique<Buffers::IndexBuffer>(p_indices);

	m_vertexArray->AddBuffer(*m_vboPosition, 3, Buffers::GLType::FLOAT);
	m_vertexArray->AddBuffer(*m_vboTextCoords, 2, Buffers::GLType::FLOAT);
	m_vertexArray->AddBuffer(*m_vboNormal, 3, Buffers::GLType::FLOAT);
	m_vertexArray->AddBuffer(*m_vboTangent, 3, Buffers::GLType::FLOAT);
	m_vertexArray->AddBuffer(*m_vboBitangent, 3, Buffers::GLType::FLOAT);

	m_vertexArray->Unbind();
}
