#include "Sound.h"

std::shared_ptr<Sound> Sound::s_pSound = nullptr;
bool Sound::m_bInit = false;

Sound::~Sound() {
}

void Sound::LoadSound() {

	if (m_bInit) return;
	m_bInit = true;

	if (!FILEMANAGER->FileExists(FILEMANAGER->GetSoundFilepath())) return;
	std::string str = FILEMANAGER->GetSoundFilepath();
	CHapiXML xml = FILEMANAGER->GetSoundFilepath();

	std::vector<CHapiXMLNode*> nodes = xml.GetAllNodesWithName("file");

	for (auto& node : nodes) {

		CHapiXMLAttribute attr;

		if (!node->GetAttributeWithName("filepath", attr)) return;

		if (!HAPI.LoadSound(node->GetAttributes()[0].AsString())) {

			throw std::runtime_error{ "unable to find sound file" };
			continue;

		}

		m_vecstrSound.push_back(node->GetAttributes()[0].AsString());

	}

}

