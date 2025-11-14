#ifndef VEHICLE_HPP
#define VEHICLE_HPP


#include "Object.h"
#include "IDisplay.hpp"
#include <vector>


class Vehicle : public Object{
public:

	using TCont = std::vector<IDisplay::Sptr>;

	void Attach(IDisplay::Sptr display);

	void Detach(IDisplay::Sptr display);

protected:

	void Notify();

	Vehicle() = default;

private:
	TCont m_display_observers;
};

#endif // !VEHICLE_HPP