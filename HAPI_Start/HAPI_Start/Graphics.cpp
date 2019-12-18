#include "Graphics.h"

std::shared_ptr<Graphics> Graphics::s_pGraphics = nullptr;
bool Graphics::m_bCreateWindow = false;

Graphics::Graphics() {

	m_rectScreen = std::make_shared<Rectangle>(m_cnWidth, m_cnHeight);

}

void Graphics::DrawBackground(Texture& t) {

	BYTE* tempScreenPtr = m_pScreen;
	BYTE* tPtr = t.GetPointer();

	if ("backgroundZ_4" == t.GetAlias()) {

		memmove(tempScreenPtr, tPtr, (m_cnWidth * m_cnHeight) << 2);
		return;

	}

	int i{ 0 };

	for (int y{ 0 }; y < m_cnHeight; y++) {

		for (int x{ 0 }; x < m_cnWidth; x++) {

			if (255 == tPtr[i + GREEN]) {

				i += BYTESPERPIXEL;
				continue; //may have to add checks for no red or blue

			}
			
			//memmove(&tempScreenPtr[i], &tPtr[i], BYTESPERPIXEL);
			memcpy(&tempScreenPtr[i], &tPtr[i], BYTESPERPIXEL);
			i += BYTESPERPIXEL;

		}

	}

}

void Graphics::CreateWindow() {

	if (m_bCreateWindow) return;
	m_bCreateWindow = true;

	try {

		HAPI.Initialise(const_cast<int&>(m_cnWidth), const_cast<int&>(m_cnHeight), m_cstrTitle); 
		HAPI.SetShowFPS(true);
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

	int i{ 0 };
	const int eol = (m_cnWidth - e.GetTexture()->GetWidth()) * BYTESPERPIXEL;
	int nPosX = e.GetPosition().x;
	int nPosY = e.GetPosition().y;

	rect->Translate(nPosX, nPosY);

	if (rect->Outside(*m_rectScreen)) return; //if the rectangle is offscreen dont render it

	rect->ClipTo(*m_rectScreen);

	const int nWidthToDraw = std::abs(rect->GetLeft() - rect->GetRight()); //calculates what length and width of the rectangle to draw and any offset necessary if not starting from 0
	const int nHeightToDraw = std::abs(rect->GetBottom() - rect->GetTop());
	int nTexOffsetX = std::abs(e.GetTexture()->GetWidth() - nWidthToDraw) << 2;
	const int nTexOffsetY = std::abs(((e.GetTexture()->GetHeight() - nHeightToDraw) * e.GetTexture()->GetWidth()) << 2);

	rect->Translate(-nPosX, -nPosY);

	if (nPosX < 0) nPosX = 0;
	if (nPosY < 0) nPosY = 0;

	BYTE* tempScreenPtr = m_pScreen + ((nPosX + (static_cast<size_t>(nPosY) * m_cnWidth)) << 2);//* BYTESPERPIXEL;
	BYTE* tPtr = e.GetTexturePointer() + (static_cast<size_t>(e.GetTexture()->GetCurrentFrame()) * e.GetWidth()) * 4;

	if (e.GetTexture()->IsAnim()) {

		nTexOffsetX = (std::abs(e.GetTexture()->GetWidth() - nWidthToDraw) + ((e.GetTexture()->GetMaxFrames() - 1) * e.GetWidth())) << 2; //changes per frame of anim 

	}

	if (rect->GetTop() != 0) tPtr += nTexOffsetY;
	if (rect->GetLeft() != 0) tPtr += nTexOffsetX;

	for (int y{ 0 }; y < nHeightToDraw; y++) { //draw height of the object in window bounds

		for (int x{ 0 }; x < nWidthToDraw; x++) { //draw width of object in window bounds


			if (245 <= tPtr[i + ALPHA]) { //memcpy if alpha isnt required

				memmove(&tempScreenPtr[i], &tPtr[i], BYTESPERPIXEL);
				i += BYTESPERPIXEL;

			}

			else { //access the bytes directly for the rgb channels

				tempScreenPtr[i] = tempScreenPtr[i] + ((tPtr[i + ALPHA] * (tPtr[i] - tempScreenPtr[i])) >> 8); //red
				tempScreenPtr[i + GREEN] = tempScreenPtr[i + GREEN] + ((tPtr[i + ALPHA] * (tPtr[i + GREEN] - tempScreenPtr[i + GREEN])) >> 8); //green
				tempScreenPtr[i + BLUE] = tempScreenPtr[i + BLUE] + ((tPtr[i + ALPHA] * (tPtr[i + BLUE] - tempScreenPtr[i + BLUE])) >> 8); //blue

				i += BYTESPERPIXEL;

			}

		}

		tPtr += nTexOffsetX; //for everyline offset if needed
		tempScreenPtr += ((static_cast<size_t>(m_cnWidth) - nWidthToDraw) << 2); //offset pointer

	}

}

void Graphics::ClearScreen() const {

	memset(m_pScreen, 0, m_cnScreenSize);

}

Graphics::~Graphics()
{
}
