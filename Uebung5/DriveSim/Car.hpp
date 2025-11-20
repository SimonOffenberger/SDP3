/*****************************************************************//**
 * \file   Car.hpp
 * \brief  Declares the Car class, a Vehicle implementation using an RPM
 *         sensor to calculate its current speed.
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

 /**
  * \class Car
  * \brief Vehicle subclass that calculates speed using an RPM sensor.
  */
class Car : public Vehicle {
public:

    /**
     * \brief Shared pointer alias for Car.
     */
    using Sptr = std::shared_ptr<Car>;

    /**
     * \brief Weak pointer alias for Car.
     */
    using Wptr = std::weak_ptr<Car>;

    /**
     * \brief Error message for invalid wheel diameter.
     */
    static inline const std::string ERROR_WHEEL_DIA_0 = "ERROR: Wheel Diameter cannot be 0!";

    /**
     * \brief Error message for null sensor pointer.
     */
    inline static const std::string ERROR_NULLPTR = "ERROR Nullptr";

    /**
     * \brief Retrieves RPM data from the sensor and updates internal state.
     *
     * This method calls RPM_Sensor::GetRevolutions() to update the current
     * wheel RPM. If the sensor throws an exception, the internal RPM value
     * is reset to zero before rethrowing the exception.
     *
     * After processing sensor data, this method notifies all observers
     * through Vehicle::Notify().
     *
     * \throws Any exception thrown by the underlying RPM sensor.
     */
    void Process();

    /**
     * \brief Computes the current speed of the car in kilometers per hour.
     *
     * The speed is calculated using the wheel RPM, wheel diameter (in mm),
     * and conversion constants.
     *
     * The calculation is based on:
     * - converting RPM to revolutions per second
     * - converting wheel diameter to circumference (diameter * pi)
     * - converting millimeters to meters
     * - converting meters per second to kilometers per hour
     *
     * \return The current speed in KPH.
     */
    double GetCurrentSpeed();

    /**
     * \brief Constructs a Car with a wheel diameter and an RPM sensor.
     *
     * \param wheel_diameter Wheel diameter in millimeters.
     * \param wh_rpm_sen Shared pointer to an RPM sensor instance.
     *
     * \throws std::string ERROR_WHEEL_DIA_0 if wheel_diameter is zero.
     * \throws std::string ERROR_NULLPTR if wh_rpm_sen is null.
     */
    Car(const size_t& wheel_diameter, RPM_Sensor::Sptr wh_rpm_sen);

private:
    /**
     * \brief Last measured wheel revolutions per minute.
     */
    size_t m_wheel_rmp;

    /**
     * \brief Wheel diameter in millimeters.
     */
    size_t m_wheel_diameter;

    /**
     * \brief Pointer to the RPM sensor used for measurement.
     */
    RPM_Sensor::Sptr m_wheel_rpm_sensor;

    /**
     * \brief Conversion factor from meters per second to kilometers per hour.
     */
    const double mps_to_kph = 3.6;

    /**
     * \brief Number of seconds in one minute.
     */
    const double seconds_in_min = 60;

    /**
     * \brief Millimeters in one meter.
     */
    const double mm_in_m = 1000;
};

#endif // !CAR_HPP
