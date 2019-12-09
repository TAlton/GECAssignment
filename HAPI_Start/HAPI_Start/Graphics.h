#pragma once

#include <HAPI_lib.h>

using namespace HAPISPACE;

class Graphics {

public:

	~Graphics();

	static std::shared_ptr<Graphics>& GetInstance() {

		if (!s_pGraphics) {

			s_pGraphics.reset(new Graphics());

		}

		return s_pGraphics;

	}

	void CreateWindow();

private:

	Graphics();

	static std::shared_ptr<Graphics> s_pGraphics;

	unsigned char* m_pScreen{ nullptr };

	const int m_cnWidth{ 1280 },
		m_cnHeight{ 720 },
		m_cnScreenSize{ (m_cnWidth * m_cnHeight) << 2 };

	const std::string m_cstrTitle{ "" };

};

#define GRAPHICS Graphics::GetInstance()