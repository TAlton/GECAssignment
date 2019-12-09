#include "FileManager.h"

std::shared_ptr<FileManager> FileManager::s_pFileManager = nullptr;

FileManager::FileManager()
{
}


FileManager::~FileManager()
{
}

const std::string FileManager::GetSceneFilepath(const int index) {

	try {

		return this->m_cveccstrFilepaths[index];

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

	}

	catch (...) {

	}


}
