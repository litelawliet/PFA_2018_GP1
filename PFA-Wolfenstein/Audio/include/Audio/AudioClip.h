#pragma once
#include <Audio/Export.h>
#include <irrKlang.h>
#include <glm/vec3.hpp>

namespace Audio
{
	class API_AUDIO AudioClip
	{
	public:
		AudioClip() noexcept;
		~AudioClip() noexcept;

		void Play2DClip(const std::string & p_audioFile, const bool p_looped = false, const float p_volume = 1.0f) const noexcept;
		void Play3DClip(const std::string & p_audioFile, const glm::vec3& p_position, const bool p_looped = false, const float p_volume = 1.0f) const noexcept;
	private:
		static irrklang::ISoundEngine* m_engine;
		static unsigned int m_engineInstanceCount;
	};
}
