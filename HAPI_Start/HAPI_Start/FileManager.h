#pragma once

#include <vector>
#include <string>
#include <memory>
#include <stdexcept>

class FileManager {

public:

	~FileManager();

	const std::string GetTextureFilepath() const { return this->m_cstrTextureFilepath; }
	const std::string GetSceneFilepath(const int index);
	bool FileExists(const std::string filepath);

	static std::shared_ptr<FileManager>& GetInstance () {

		if (!s_pFileManager) {

			s_pFileManager.reset(new FileManager());

		}

		return s_pFileManager;

	}

private:

	FileManager() = default;

	static std::shared_ptr<FileManager> s_pFileManager;

	const std::string m_cstrTextureFilepath{ "Data\\XML\\Texture\\Texture.xml" };
	const std::vector<std::string> m_cveccstrFilepaths{ "Data\\XML\\Scene\\Scene1.xml",
															"Data\\XML\\Scene\\Scene2.xml",
															"Data\\XML\\Scene\\Scene3.xml" };
};

#define FILEMANAGER FileManager::GetInstance()