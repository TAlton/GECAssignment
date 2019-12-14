#include "Texture.h"



Texture::~Texture()
{

	delete m_pTexture;

}

void Texture::LoadTexture() {

	try {

		int width = static_cast<int>(m_shHeight);
		int height = static_cast<int>(m_shWidth);
		HAPI.LoadTexture(m_strAlias, &m_pTexture, width, height);

		this->m_shHeight = height;

		if (!m_bIsAnim) {

			this->m_shWidth = width;

		}
		else {

			this->m_shMaxFrames = width / 64;
			this->m_shWidth = (width / m_shMaxFrames);

		}

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
