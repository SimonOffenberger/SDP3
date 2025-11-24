/*****************************************************************//**
 * \file   Meter.cpp
 * \brief  Abstract base class for all meter display types.
 *
 * \author Simon
 * \date   November 2025
 *********************************************************************/
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
