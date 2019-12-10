#pragma once

#include <HAPI_lib.h>

using namespace HAPISPACE;

class Texture {

public:

	Texture() = default;
	Texture(const std::string filepath) : m_strAlias(filepath) {}
	Texture(int width, int height) : m_shWidth(static_cast<short>(width)), m_shHeight(static_cast<short>(height)) {}
	Texture(int width, int height, unsigned char* ptr) : m_shWidth(static_cast<short>(width)), m_shHeight(static_cast<short>(height)), m_pTexture(ptr) {}
	Texture(short width, short height) : m_shWidth(width), m_shHeight(height) {}
	Texture(short width, short height, unsigned char* ptr) : m_shWidth(width), m_shHeight(height), m_pTexture(ptr) {}
	Texture(const Texture& tex) {

		this->m_shWidth = tex.GetWidth();
		this->m_shHeight = tex.GetHeight();
		this->m_strAlias = tex.GetAlias();
		this->m_pTexture = tex.GetPointer();

	}

	~Texture();

	short GetWidth() const { return this->m_shWidth; }
	short GetHeight() const { return this->m_shHeight; }
	unsigned char* GetPointer() const { return this->m_pTexture; }
	std::string GetAlias() const { return this->m_strAlias; }

	void LoadTexture();

private:

	short m_shWidth{ 0 },
		m_shHeight{ 0 };

	std::string m_strAlias{ "default" };

	unsigned char* m_pTexture{ nullptr };

};

