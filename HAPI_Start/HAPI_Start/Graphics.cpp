#include "Graphics.h"

std::shared_ptr<Graphics> Graphics::s_pGraphics = nullptr;

Graphics::Graphics() {

	m_rectScreen = std::make_shared<Rectangle>(m_cnWidth, m_cnHeight);

}

void Graphics::CreateWindow() {

	try {

		HAPI.Initialise(const_cast<int&>(m_cnWidth), const_cast<int&>(m_cnHeight), m_cstrTitle); 
		//casting constness to allow for const vars that are initialised here
		m_pScreen = HAPI.GetScreenPointer();

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

	catch (std::runtime_error& e) {

		throw e;

	}

	catch (...) {

	}

}

void Graphics::Draw(Entity& e) {

	std::shared_ptr<Rectangle> rect;
	rect = std::make_shared<Rectangle>(*e.GetRectangle());

	e.GetTexture()->GetWidth();

	int i{ 0 };
	const int eol = (m_cnWidth - e.GetTexture()->GetWidth()) * BytesPerPixel;
	int nPosX = e.GetPosition().x;
	int nPosY = e.GetPosition().y;

	rect->Translate(nPosX, nPosY);

	if (rect->Outside(*m_rectScreen)) return; //if the rectangle is offscreen dont render it

	rect->ClipTo(*m_rectScreen);

	int nWidthToDraw = std::abs(rect->GetLeft() - rect->GetRight());
	int nHeightToDraw = std::abs(rect->GetBottom() - rect->GetTop());
	int nTexOffsetX = std::abs(e.GetTexture()->GetWidth() - nWidthToDraw) * 4;
	int nTexOffsetY = std::abs(((e.GetTexture()->GetHeight() - nHeightToDraw) * e.GetTexture()->GetWidth()) * 4);

	rect->Translate(-nPosX, -nPosY);

	if (nPosX < 0) nPosX = 0;
	if (nPosY < 0) nPosY = 0;

	BYTE* tempBufferPtr = m_pScreen + (nPosX + (static_cast<size_t>(nPosY) * m_cnWidth)) * BytesPerPixel;
	BYTE* tPtr = e.GetTexturePointer();

	if (rect->GetTop() != 0) tPtr += nTexOffsetY;
	if (rect->GetLeft() != 0) tPtr += nTexOffsetX;

	for (int y{ 0 }; y < nHeightToDraw; y++) { //draw height of the object in window bounds

		for (int x{ 0 }; x < nWidthToDraw; x++) { //draw width of object in window bounds


			if (250 <= tPtr[i + Alpha]) { //memcpy if alpha isnt required

				memcpy(&tempBufferPtr[i], &tPtr[i], BytesPerPixel);
				i += BytesPerPixel;

			}

			else { //access the bytes directly for the rgb channels

				tempBufferPtr[i] = tempBufferPtr[i] + ((tPtr[i + Alpha] * (tPtr[i] - tempBufferPtr[i])) >> 8); //red
				tempBufferPtr[i + Green] = tempBufferPtr[i + Green] + ((tPtr[i + Alpha] * (tPtr[i + Green] - tempBufferPtr[i + Green])) >> 8); //green
				tempBufferPtr[i + Blue] = tempBufferPtr[i + Blue] + ((tPtr[i + Alpha] * (tPtr[i + Blue] - tempBufferPtr[i + Blue])) >> 8); //blue

				i += BytesPerPixel;

			}

		}

		tPtr += nTexOffsetX; //for everyline offset if needed
		tempBufferPtr += ((static_cast<size_t>(m_cnWidth) - nWidthToDraw) << 2); //offset pointer

	}

}

void Graphics::ClearScreen() const {

	memset(m_pScreen, 0, m_cnScreenSize);

}


Graphics::~Graphics()
{
}
