#include "Meter.hpp"

void Meter::SetDisplay(WindowsDisplay::SPtr display)
{

	if (display == nullptr) throw Meter::ERROR_NULLPTR;

	m_window = move(display);
}

Meter::Meter(WindowsDisplay::SPtr display)
{
	if (display == nullptr) throw Meter::ERROR_NULLPTR;

	m_window = move(display);
}
