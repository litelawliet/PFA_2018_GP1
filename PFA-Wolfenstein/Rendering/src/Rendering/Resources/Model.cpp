#include <stdafx.h>
#include <Rendering/Resources/Model.h>
#include <Rendering/Geometry/Vertex.h>
#include <assimp/Importer.hpp>
#include <assimp/postprocess.h>
#include <assimp/scene.h>
#include <Rendering/Resources/Mesh.h>
#include <Rendering/Resources/Loaders/ShaderLoader.h>


Rendering::Resources::Model::Model(const std::string& p_path) noexcept
	: m_modelPath{ std::move(p_path) }
{
	LoadModel(p_path);
	LoadShader();
}

Rendering::Resources::Model::Model(const std::string& p_modelPath,
	const std::string& p_vertexFilepath,
	const std::string& p_fragmentFilepath) noexcept
{
	LoadModel(p_modelPath);
	LoadShader(p_vertexFilepath, p_fragmentFilepath);
}

Rendering::Resources::Model::Model(const Model& p_other) noexcept
{
	m_modelPath = p_other.m_modelPath;
	m_mesh = p_other.m_mesh;
	m_shader = p_other.m_shader;
}

void Rendering::Resources::Model::AddTexture(const std::string& p_texturePath) const
{
	m_mesh->AddTexture(p_texturePath);
}

void Rendering::Resources::Model::AddNormalMap(const std::string& p_texturePath) const
{
	m_mesh->AddNormalMap(p_texturePath);
}

void Rendering::Resources::Model::LoadModel(const std::string& p_path) noexcept
{
	Assimp::Importer importer;
	const aiScene*   scene = importer.ReadFile(p_path.c_str(),
		aiProcess_CalcTangentSpace |
		aiProcess_GenNormals |
		//aiProcess_JoinIdenticalVertices |
		//aiProcess_ImproveCacheLocality |
		//aiProcess_LimitBoneWeights |
		aiProcess_RemoveRedundantMaterials |
		//aiProcess_SplitLargeMeshes |
		aiProcess_Triangulate |
		aiProcess_GenUVCoords |
		//aiProcess_SortByPType |
		//aiProcess_FindDegenerates |
		//aiProcess_FindInvalidData |
		aiProcess_OptimizeMeshes |
		//aiProcess_OptimizeGraph |
		aiProcess_PreTransformVertices |
		0);

	if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode)
	{
		std::cout << "ERROR::ASSIMP::" << importer.GetErrorString() << std::endl;
		return;
	}

	//Iterate over the meshes
	for (unsigned int i = 0; i < scene->mNumMeshes; ++i)
	{
		aiMesh* mesh = scene->mMeshes[i];
		ProcessMesh(mesh);
	}
	m_mesh = std::make_shared<Mesh>(std::move(m_vertices), std::move(m_indices));

}

void Rendering::Resources::Model::LoadShader(const std::string& p_vertexFilepath,
	const std::string& p_fragmentFilepath) noexcept
{
	m_shader = std::make_shared<Shader>(*Loaders::ShaderLoader::
		Load(p_vertexFilepath, p_fragmentFilepath));
}

const std::string& Rendering::Resources::Model::GetModelPath() const
{
	return m_modelPath;
}

void Rendering::Resources::Model::Bind() const noexcept
{
	m_mesh->Bind();
	m_shader->Bind();
	m_mesh->BindTextures();
}

void Rendering::Resources::Model::Unbind() const noexcept
{
	m_mesh->UnbindTextures();
	m_shader->Unbind();
	m_mesh->Unbind();
}


void Rendering::Resources::Model::ProcessMesh(aiMesh* p_mesh) noexcept
{
	for (unsigned int j = 0; j < p_mesh->mNumVertices; ++j)
	{
		//Create a vertex to store the mesh's vertices temporarily
		Rendering::Geometry::Vertex tempVertex;

		//Set the positions
		tempVertex.m_position[0] = p_mesh->mVertices[j].x;
		tempVertex.m_position[1] = p_mesh->mVertices[j].y;
		tempVertex.m_position[2] = p_mesh->mVertices[j].z;

		//Set the textures coordinates

		if (p_mesh->mTextureCoords[0] != nullptr) {
			aiVector3D* textureVec = &p_mesh->mTextureCoords[0][j];
			//printf("tex (%f,%f,%f)", textureVec->x, textureVec->y, textureVec->z );
			tempVertex.m_textCoords[0] = textureVec->x;
			tempVertex.m_textCoords[1] = textureVec->y;
		}

		if (p_mesh->HasTangentsAndBitangents())
		{
			tempVertex.m_tangent[0] = p_mesh->mTangents[j].x;
			tempVertex.m_tangent[1] = p_mesh->mTangents[j].y;
			tempVertex.m_tangent[2] = p_mesh->mTangents[j].z;

			tempVertex.m_tangent[0] = p_mesh->mBitangents[j].x;
			tempVertex.m_tangent[1] = p_mesh->mBitangents[j].y;
			tempVertex.m_tangent[2] = p_mesh->mBitangents[j].z;
		}

		//Set the normals
		tempVertex.m_normal[0] = p_mesh->mNormals[j].x;
		tempVertex.m_normal[1] = p_mesh->mNormals[j].y;
		tempVertex.m_normal[2] = p_mesh->mNormals[j].z;

		//Add the vertex to the vertices vector
		m_vertices.push_back(tempVertex);
	}

	//Iterate over the faces of the mesh
	for (unsigned int j = 0; j < p_mesh->mNumFaces; ++j)
	{
		//Get the face
		const auto face = p_mesh->mFaces[j];
		//Add the indices of the face to the vector
		for (unsigned int k = 0; k < face.mNumIndices; ++k)
		{
			m_indices.push_back(face.mIndices[k] + m_offset);
		}
	}

	m_offset += static_cast<unsigned int>(m_vertices.size());
}