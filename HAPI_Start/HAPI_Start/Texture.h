#pragma once

#include <HAPI_lib.h>

using namespace HAPISPACE;

class Texture {

public:

	Texture() = default;
	Texture(const std::string filepath, bool isAnim, bool isBackground = false) : m_strAlias(filepath), m_bIsAnim(isAnim), m_bIsBackground(isBackground) {} // should pass in frame width as well but used as Proof of concept
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
	bool IsAnim() const { return this->m_bIsAnim; }
	bool IsBackground() const { return this->m_bIsBackground; }
	short GetMaxFrames() const { return this->m_shMaxFrames; }
	short GetCurrentFrame() const { return this->m_shCurrentFrame; }

	void SetCurrentFrame() {

		if (m_shCurrentFrame == m_shMaxFrames) {

			this->m_shCurrentFrame = 0;

		}
		else {

			m_shCurrentFrame++;

		}
	}

	void SetCurrentFrame(int i) {

		if (i >= 0 && i <= m_shMaxFrames) {

			m_shCurrentFrame = i;

		}

	}

	void LoadTexture();

private:

	short m_shWidth{ 0 },
		m_shHeight{ 0 },
		m_shMaxFrames{ 0 },
		m_shCurrentFrame{ 0 };

	bool m_bIsAnim{ false },
		m_bIsBackground{ false };

	std::string m_strAlias{ "default" };

	unsigned char* m_pTexture{ nullptr };

};

