#pragma once
#include <Rendering/Export.h>
#include <Rendering/Resources/Mesh.h>
#include <Rendering/Resources/Shader.h>
#include <assimp/scene.h>
#include <vector>
#include <string>
#include <memory>

namespace Rendering::Resources
{
	class API_RENDERING Model
	{
	public:
		Model() noexcept = default;
		explicit Model(const std::string& p_path) noexcept;
		Model(const std::string& p_modelPath,
			const std::string& p_vertexFilepath,
			const std::string& p_fragmentFilepath) noexcept;

		Model(const Model& p_other) noexcept;

		void AddTexture(const std::string & p_texturePath) const;
		void AddNormalMap(const std::string & p_texturePath) const;

		std::shared_ptr<Mesh>& GetMesh() noexcept { return m_mesh; }

		std::shared_ptr<Shader>& GetShader() noexcept { return m_shader; }

		std::shared_ptr<Texture>& GetTexture() const noexcept { return m_mesh->GetTexture(); };

		std::shared_ptr<Texture>& GetNormalMap() const noexcept { return m_mesh->GetNormalMap(); }

		const std::string & GetModelPath() const;

		void Bind() const noexcept;
		void Unbind() const noexcept;

	private:
		std::string				m_modelPath;

		std::shared_ptr<Shader> m_shader;
		std::shared_ptr<Mesh>   m_mesh;

		std::vector<Rendering::Geometry::Vertex> m_vertices;
		std::vector<GLuint>                      m_indices;
		unsigned int m_offset = 0;

		/*  Functions   */
		void LoadModel(const std::string& path) noexcept;
		void ProcessMesh(aiMesh* p_mesh) noexcept;

		/**
		 * @brief Method who can lod a shader. If no parameters are send, it loads both the default vertex and fragment shader.
		 * @param p_vertexFilepath : Vertex Shader to load.
		 * @param p_fragmentFilepath : Fragment Shader to load.
		**/
		void LoadShader(
			const std::string& p_vertexFilepath =
			"../rsc/shaders/defaultShader.vert",
			const std::string& p_fragmentFilepath =
			"../rsc/shaders/defaultShader.frag") noexcept;
	};
}
