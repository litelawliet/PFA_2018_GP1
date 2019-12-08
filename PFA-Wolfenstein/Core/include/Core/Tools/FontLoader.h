#pragma once
#include <map>
#include <ft2build.h>
#include FT_FREETYPE_H
#include <Core/Tools/Character.h>
#include <Rendering/Resources/Shader.h>
#include <glm/vec3.hpp>

namespace Core::Tools
{
	class FontLoader
	{
	public:
		FontLoader();
		~FontLoader() = default;

		void RenderText(Rendering::Resources::Shader &s, std::string text, GLfloat x, GLfloat y, GLfloat scale, glm::vec3 color);

	private:
		std::map<GLchar, Character> m_characters;
		GLuint m_VAO;
		GLuint m_VBO;
	};
}

