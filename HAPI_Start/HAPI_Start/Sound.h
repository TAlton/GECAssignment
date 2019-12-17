#pragma once

#include <memory>
#include <vector>
#include <string>

class Sound {

public:

	~Sound();

	static std::shared_ptr<Sound> s_pSound;

	static std::shared_ptr<Sound>& GetInstance() {

		if (!s_pSound) {

			s_pSound.reset(new Sound());

			return s_pSound;

		}

		return s_pSound;

	}

private:

	Sound() = default;

	std::vector<std::string> m_vecstrSound;

};

#define SOUND Sound::GetInstance()