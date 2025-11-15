#include "Tachometer.hpp"

#include <iostream>

void Tachometer::Update()
{
	m_speed = m_car->GetCurrentSpeed();
	m_window->SendValue(m_speed);
}

Tachometer::Tachometer(Car::Sptr car, WindowsDisplay::SPtr display) : m_speed{ 0 }, Meter{move( display )}
{
	if (car == nullptr) throw Tachometer::ERROR_NULLPTR;

	m_car = car;
}
