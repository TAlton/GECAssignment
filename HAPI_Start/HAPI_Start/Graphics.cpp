#include "Graphics.h"

std::shared_ptr<Graphics> Graphics::s_pGraphics = nullptr;

Graphics::Graphics() {



}

void Graphics::CreateWindow() {

	try {

		HAPI.Initialise(const_cast<int&>(m_cnWidth), const_cast<int&>(m_cnHeight), m_cstrTitle); 
		//casting constness to allow for const vars that are initialised here

	}

	catch (std::overflow_error & e) {

		throw e;

	}

	catch (std::underflow_error & e) {

		throw e;

	}

	catch (std::invalid_argument & e) {

		throw e;

	}

	catch (std::runtime_error & e) {

	}

	catch (...) {

	}

}


Graphics::~Graphics()
{
}
