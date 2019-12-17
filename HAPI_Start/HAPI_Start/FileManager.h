#pragma once

#include <vector>
#include <string>
#include <memory>
#include <stdexcept>

class FileManager {

public:

	~FileManager();

	std::string GetTextureFilepath() { return this->m_strTextureFilepath; }
	std::string GetSceneFilepath(const int index);
	std::string GetUIFilepath() { return this->m_strUIFilepath; }
	bool FileExists(const std::string filepath);

	static std::shared_ptr<FileManager>& GetInstance () {

		if (!s_pFileManager) {

			s_pFileManager.reset(new FileManager());

		}

		return s_pFileManager;

	}

private:

	FileManager();

	static std::shared_ptr<FileManager> s_pFileManager;

	std::string m_strTextureFilepath{ "Data\\XML\\Texture\\Textures.xml" };
	std::string m_strUIFilepath{ "Data\\XML\\UserInterface\\UI.xml" };
	std::vector<std::string> m_vecstrFilepaths{ "Data\\XML\\Scene\\Scene1.xml",
															"Data\\XML\\Scene\\Scene2.xml",
															"Data\\XML\\Scene\\Scene3.xml" };
};

#define FILEMANAGER FileManager::GetInstance()