#pragma once

#include "FileManager.h"

#include <HAPI_lib.h>

using namespace HAPISPACE;

enum eSound : int { SHOOT = 0 };

class Sound {

public:

	~Sound();

	static std::shared_ptr<Sound>& GetInstance() {

		if (!s_pSound) {

			s_pSound.reset(new Sound());

			return s_pSound;

		}

		return s_pSound;

	}

	void LoadSound();
	std::string GetSound(int i) const { return this->m_vecstrSound[i]; }

private:

	Sound() = default;

	static std::shared_ptr<Sound> s_pSound;

	static bool m_bInit;

	std::vector<std::string> m_vecstrSound;

};

#define SOUND Sound::GetInstance()