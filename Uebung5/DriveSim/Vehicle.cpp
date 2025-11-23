/*****************************************************************//**
 * \file   Vehicle.cpp
 * \brief  Base class representing a generic vehicle that supports
 *         display observers following the Observer design pattern.
 *
 * The Vehicle class manages a collection of display observers that
 * implement the IDisplay interface. Observers can be attached or
 * detached at runtime.
 *
 * \author Simon
 * \date   November 2025
 *********************************************************************/
#include "Vehicle.hpp"
#include "algorithm"

using namespace std;

void Vehicle::Attach(IDisplay::Sptr display)
{
	if (display == nullptr) throw Vehicle::ERROR_NULLPTR;

	m_display_observers.emplace_back(move(display));
}

void Vehicle::Detach(IDisplay::Sptr display)
{
	if (display == nullptr) throw Vehicle::ERROR_NULLPTR;

	const auto it = find(m_display_observers.cbegin(), m_display_observers.cend(), display);

	if (it != m_display_observers.cend()) {
		m_display_observers.erase(it);
	}
}

void Vehicle::Notify() const
{
	for_each(m_display_observers.cbegin(), m_display_observers.cend(),
		[](auto& obs) { if(obs != nullptr) obs->Update();});
}
