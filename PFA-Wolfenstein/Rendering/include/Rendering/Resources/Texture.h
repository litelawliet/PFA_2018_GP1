#pragma once
#include <GLFW/glfw3.h>
#include <Rendering/Export.h>
#include <Rendering/Context/IWindow.h>

namespace Rendering::Resources
{
	class API_RENDERING Texture
	{
	public:
		Texture();
		~Texture();

		void Bind(const int p_slot) const;
		void Unbind() const;

		void Load(const std::string& p_filepath, const int p_slot);

		bool IsTextureSet() const { return m_loaded; }

		const std::string & GetTexturePath() const;

	private:
		GLuint m_id{ 0u };
		std::string m_texturePath;
		bool m_loaded;
	};
}
