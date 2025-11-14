#include "Vehicle.hpp"
#include "algorithm"

using namespace std;

void Vehicle::Attach(IDisplay::Sptr display)
{
	m_display_observers.push_back(move(display));
}

void Vehicle::Detach(IDisplay::Sptr display)
{
	auto it = find(m_display_observers.cbegin(), m_display_observers.cend(), display);
	if (it != m_display_observers.cend()) {
		m_display_observers.erase(it);
	}
}

void Vehicle::Notify()
{
	for_each(m_display_observers.cbegin(), m_display_observers.cend(),
		[](auto& obs) { obs->Update();});
}
