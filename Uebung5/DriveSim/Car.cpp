#include "Car.hpp"
#include <numbers>

void Car::Process()
{
	m_wheel_rmp = m_wheel_rpm_sensor->GetRevolutioins();
	Notify();
}

double Car::GetCurrentSpeed()
{
	return ((m_wheel_rmp / 60) * m_wheel_diameter * std::numbers::pi * 3.6) / 1000;
}

Car::Car(const unsigned int & wheel_diameter, RPM_Sensor::Sptr wh_rpm_sen) : m_wheel_rmp{0}
{
	if (wheel_diameter == 0) throw Car::ERROR_WHEEL_DIA_0;
	if (wh_rpm_sen == nullptr) throw Car::ERROR_NULLPTR;

	m_wheel_rpm_sensor = move(wh_rpm_sen);

	m_wheel_diameter = wheel_diameter;
}
