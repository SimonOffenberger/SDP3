#include "Odometer.hpp"

void Odometer::Update()
{

	Car::Sptr car = m_car.lock();

	if (car == nullptr) throw Odometer::ERROR_NULLPTR;

	const double speed = abs(car->GetCurrentSpeed());

	m_milage = m_milage + (speed * Odometer::Update_Intervall)/ mseconds_in_hours;

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