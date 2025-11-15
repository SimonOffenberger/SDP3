#include "Meter.hpp"

Meter::Meter(WindowsDisplay::SPtr display)
{
	if (display == nullptr) throw Meter::ERROR_NULLPTR;

	m_window = move(display);
}
