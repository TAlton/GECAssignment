#include "FileManager.h"

std::shared_ptr<FileManager> FileManager::s_pFileManager = nullptr;

FileManager::FileManager() {
}

FileManager::~FileManager()
{
}

std::string FileManager::GetSceneFilepath(const int index) {

	try {

		m_vecstrFilepaths[index];

	}
	catch (std::out_of_range& e) {

		throw e;

	}

	catch (std::range_error& e) {

		throw e;

	}

	catch (std::invalid_argument& e) {

		throw e;

	}

	catch (std::runtime_error& e) {

		throw e;

	}

	catch (...) {

	}

	return m_vecstrFilepaths[index];

}

bool FileManager::FileExists(const std::string filepath) {

	struct stat buf;

	if (stat(filepath.c_str(), &buf) != -1) return true; //checks the state of the file if it exists

	return false;

}
