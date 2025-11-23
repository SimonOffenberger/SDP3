/*****************************************************************//**
 * \file   Odometer.cpp
 * \brief  Display that calculates and shows the current mileage of a car.
 *
 * \author Simon
 * \date   November 2025
 *********************************************************************/
#include "Odometer.hpp"

void Odometer::Update()
{

	Car::Sptr car = m_car.lock();

	if (car == nullptr) throw Odometer::ERROR_NULLPTR;

	// get the absolute value of the Current Speed 
	// negative Speed does not make the milage go down!
	const double speed = abs(car->GetCurrentSpeed());

	// Integrate the speed over the update interval to get the distance
	m_milage = m_milage + (speed * Odometer::Update_Intervall)/ mseconds_in_hours;

	// If a display is set, send the new milage value
	if(m_window != nullptr) m_window->SendValue(static_cast<unsigned int>(m_milage));
}

Odometer::Odometer(Car::Sptr car, WindowsDisplay::SPtr display) : m_milage { 0 }, Meter{ move(display) }
{
	if (car == nullptr) throw Odometer::ERROR_NULLPTR;

	m_car = move(car);
}

Odometer::Odometer(Car::Sptr car) : m_milage{ 0 }
{
	if (car == nullptr) throw Odometer::ERROR_NULLPTR;

	m_car = move(car);
}


size_t Odometer::GetMilage() const
{
	return static_cast<size_t>(m_milage);
}