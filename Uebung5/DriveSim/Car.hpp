/*****************************************************************//**
 * \file   Car.hpp
 * \brief  A car class that uses an RPM sensor to calculate its speed
 *
 * \author Simon
 * \date   November 2025
 *********************************************************************/

#ifndef CAR_HPP
#define CAR_HPP

#include <string>
#include <string_view>
#include <memory>

#include "RPM_Sensor.hpp"
#include "Vehicle.hpp"

class Car : public Vehicle {
public:
	/**
     * \brief Shared pointer type for Car
	 */
	using Sptr = std::shared_ptr<Car>;

	static inline const std::string ERROR_WHEEL_DIA_0 = "ERROR: Wheel Diameter cannot be 0!";

	/**
     * \brief Gets data from the RPM sensor
	 */
	void Process();

	/**
     * \brief Calculated current speed of the car in KPH
     * \return double speed in KPH
	 */
	double GetCurrentSpeed();

	Car(const unsigned int & wheel_diameter, RPM_Sensor::Sptr wh_rpm_sen);

protected:

private:
	unsigned int m_wheel_rmp;
	unsigned int m_wheel_diameter;
	RPM_Sensor::Sptr m_wheel_rpm_sensor;

	const double mps_to_kph = 3.6;
    const double seconds_in_min = 60;
	const double mm_in_m = 1000;
};

#endif // !CAR_HPP
