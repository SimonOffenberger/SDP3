/*****************************************************************//**
 * \file   Vehicle.hpp
 * \brief  Test Driver for the Drive Sim
 *
 * \author Simon
 * \date   November 2025
 *********************************************************************/

#ifndef VEHICLE_HPP
#define VEHICLE_HPP


#include "Object.h"
#include "IDisplay.hpp"
#include <vector>


class Vehicle : public Object{
public:

	using TCont = std::vector<IDisplay::Sptr>;
	
	/**
     * \brief Attach a display to the vehicle
	 */
	void Attach(IDisplay::Sptr display);

	/**
     * \brief Detach a display from the vehicle
	 */
	void Detach(IDisplay::Sptr display);

protected:

    /**
     * \brief Notify all attached displays
     */
	void Notify();

	Vehicle() = default;

private:
	/**
     * \brief container that holds all attached displays
	 */
	TCont m_display_observers;
};

#endif // !VEHICLE_HPP