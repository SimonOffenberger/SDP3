/*****************************************************************//**
 * \file   Tachometer.hpp
 * \brief  A display that shows the current speed of the car
 *
 * \author Simon
 * \date   November 2025
 *********************************************************************/
#ifndef TACHOMETER_HPP
#define TACHOMETER_HPP

#include "Object.h"
#include "Meter.hpp"
#include "Car.hpp"


class Tachometer : public Meter {
public:
	/**
     * \brief Update the display to get current speed
	 */
	virtual void Update() override;

	Tachometer(Car & car, WindowsDisplay::SPtr display);
									
private:

	Car & m_car;

	double m_speed;
};


#endif // !TACHOMETER_HPP