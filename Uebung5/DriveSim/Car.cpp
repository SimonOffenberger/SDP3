#include "Car.hpp"
#include <numbers>

void Car::Process()
{
	try {
		// Get Revolutions 
		m_wheel_rmp = m_wheel_rpm_sensor->GetRevolutions();
	}
	catch (...) {

		m_wheel_rmp = 0;

		throw; // rethrow exception to inform user of the exception
	}


	Notify();
}

double Car::GetCurrentSpeed()
{
	return ((m_wheel_rmp / seconds_in_min) * m_wheel_diameter * std::numbers::pi * mps_to_kph) / mm_in_m;
}

Car::Car(const size_t& wheel_diameter, RPM_Sensor::Sptr wh_rpm_sen) : m_wheel_rmp{0}
{
	if (wheel_diameter == 0) throw Car::ERROR_WHEEL_DIA_0;
	if (wh_rpm_sen == nullptr) throw Car::ERROR_NULLPTR;

	m_wheel_rpm_sensor = move(wh_rpm_sen);

	m_wheel_diameter = wheel_diameter;
}
