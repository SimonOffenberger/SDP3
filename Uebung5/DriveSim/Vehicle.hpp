#ifndef VEHICLE_HPP
#define VEHICLE_HPP


#include "Object.h"
#include "IDisplay.hpp"
#include <vector>


class Vehicle : public Object, public IDisplay{
public:

	using TCont = std::vector<IDisplay::Uptr>;

	void Attach(IDisplay::Uptr display);

	void Detach(IDisplay::Uptr display);


protected:

	void Notify();

	Vehicle() = default;

private:
	TCont m_display_observers;
};

#endif // !VEHICLE_HPP