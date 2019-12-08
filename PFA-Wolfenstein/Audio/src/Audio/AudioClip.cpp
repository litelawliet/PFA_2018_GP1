#include "stdafx.h"
#include <Audio/AudioClip.h>

irrklang::ISoundEngine* Audio::AudioClip::m_engine = nullptr;
unsigned int Audio::AudioClip::m_engineInstanceCount = 0;

Audio::AudioClip::AudioClip() noexcept
{
	if (m_engine == nullptr)
	{
		m_engine = irrklang::createIrrKlangDevice();
		++m_engineInstanceCount;
	}
}

Audio::AudioClip::~AudioClip() noexcept
{
	--m_engineInstanceCount;
	if (m_engineInstanceCount == 0)
	{
		m_engine->drop();
	}
}

void Audio::AudioClip::Play2DClip(const std::string& p_audioFile, const bool p_looped, const float p_volume) const noexcept
{
	// Set ISound volume and keep track of sounds played somewhere
	m_engine->setSoundVolume(p_volume);
	m_engine->play2D(p_audioFile.c_str(), p_looped);
}

void Audio::AudioClip::Play3DClip(const std::string& p_audioFile, const glm::vec3& p_position, const bool p_looped, const float p_volume) const noexcept
{
	m_engine->setSoundVolume(p_volume);
	m_engine->play3D(p_audioFile.c_str(), irrklang::vec3df(p_position.x, p_position.y, p_position.z), p_looped);
}
