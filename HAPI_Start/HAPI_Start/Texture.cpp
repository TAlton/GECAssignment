#include "Texture.h"



Texture::~Texture()
{
}

void Texture::LoadTexture(const std::string& filepath) {

	try {

		int width = static_cast<int>(m_shHeight),
			height = static_cast<int>(m_shWidth);
		if (!HAPI.LoadTexture(filepath, &m_pTexture, width, height));

		this->m_shHeight = height;
		this->m_shWidth = width;

	}
	catch (std::overflow_error& e) {
		throw e;
	}
	catch (std::underflow_error& e) {
		throw e;
	}
	catch (std::invalid_argument& e) {
		throw e;
	}
	catch (...) {

	}

}
