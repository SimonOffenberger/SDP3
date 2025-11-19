#include "Tachometer.hpp"

#include <iostream>

void Tachometer::Update()
{
	m_speed = m_car.GetCurrentSpeed();
	m_window->SendValue(m_speed);
}

Tachometer::Tachometer(Car & car, WindowsDisplay::SPtr display) : m_car{car}, m_speed{0}, Meter{move(display)}
{
}
