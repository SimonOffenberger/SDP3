/*****************************************************************//**
 * \file   Tachometer.cpp
 * \brief  Display that shows the current speed of a car.
 *
 * The Tachometer observes a Car instance and displays its current speed.
 * It derives from Meter and serves as an observer in the Vehicle system.
 *
 * \author Simon
 * \date   November 2025
 *********************************************************************/

#include "Tachometer.hpp"

#include <iostream>

void Tachometer::Update()
{
	Car::Sptr car = m_car.lock();

	// check if sptr is valid
	if (car == nullptr) throw Tachometer::ERROR_NULLPTR;

	m_speed = car->GetCurrentSpeed();

	if (m_window != nullptr) m_window->SendValue(static_cast<unsigned int>(m_speed));
}

Tachometer::Tachometer(Car::Sptr car, WindowsDisplay::SPtr display) :  m_speed{0}, Meter{move(display)}
{
	if (car == nullptr) throw Tachometer::ERROR_NULLPTR;

	m_car = move(car);

}

Tachometer::Tachometer(Car::Sptr car) : m_speed{ 0 }
{
	if (car == nullptr) throw Tachometer::ERROR_NULLPTR;

	m_car = move(car);
}
