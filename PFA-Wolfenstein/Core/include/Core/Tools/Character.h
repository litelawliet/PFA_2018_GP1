#pragma once
#include <GL/glew.h>
#include <glm/vec2.hpp>

namespace Core::Tools
{
	struct Character
	{
		GLuint m_textureID;
		glm::ivec2 m_size;
		glm::ivec2 m_bearing;
		GLuint m_advance;
	};
}
