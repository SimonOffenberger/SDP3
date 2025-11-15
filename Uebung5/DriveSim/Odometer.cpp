#include "Odometer.hpp"

void Odometer::Update()
{
	double speed = m_car->GetCurrentSpeed();

	m_milage = m_milage + (speed * 0.5)/3600;

	m_window->SendValue(m_milage);
}

Odometer::Odometer(Car::Sptr car, WindowsDisplay::SPtr display) :  m_milage{ 0 }, Meter{ move(display) }
{
	if (car == nullptr) throw Odometer::ERROR_NULLPTR;

	m_car = move(car);
}
