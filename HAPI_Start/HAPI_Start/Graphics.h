#pragma once

#include <HAPI_lib.h>
#include "Entity.h"

using namespace HAPISPACE;

class Graphics {

public:

	~Graphics();

	static std::shared_ptr<Graphics>& GetInstance() {

		if (!s_pGraphics)
			s_pGraphics.reset(new Graphics());
		return s_pGraphics;

	}

	void CreateWindow();
	void Draw(Entity& e);
	void ClearScreen() const;

private:

	Graphics();

	static std::shared_ptr<Graphics> s_pGraphics;
	static bool m_bCreateWindow;

	std::shared_ptr<Rectangle> m_rectScreen = nullptr;

	unsigned char* m_pScreen{ nullptr };

	const int m_cnWidth{ 1280 },
		m_cnHeight{ 720 },
		m_cnScreenSize{ (m_cnWidth * m_cnHeight) << 2 };

	const std::string m_cstrTitle{ "Game Engine Construction - S6079142" };

};

#define GRAPHICS Graphics::GetInstance()
#define BYTESPERPIXEL 4
#define RED 0
#define GREEN 1
#define BLUE 2
#define ALPHA 3