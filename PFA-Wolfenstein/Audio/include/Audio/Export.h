#pragma once

#pragma warning(disable:4251)

#ifdef AUDIO_CONTEXT
#define API_AUDIO __declspec(dllexport)
#else
#define API_AUDIO __declspec(dllimport)
#endif
