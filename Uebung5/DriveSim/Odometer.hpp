/*****************************************************************//**
 * \file   Odometer.hpp
 * \brief  A display that shows the current milage of the car
 *
 * \author Simon
 * \date   November 2025
 *********************************************************************/
#ifndef ODOMETER_HPP
#define ODOMETER_HPP

#include "Object.h"
#include "Meter.hpp"
#include "Car.hpp"

class Odometer :public Meter {
public:
	/**
     * \brief Update the display to get current milage
	 */
	virtual void Update() override;

	/**
     * \brief Constructor of Odometer
	 */
	Odometer(Car & car, WindowsDisplay::SPtr display);
						
private:

	Car & m_car;

	double m_milage;
};


#endif // !ODOMETER_HPP
