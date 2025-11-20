/*****************************************************************//**
 * \file   Odometer.hpp
 * \brief  Display that calculates and shows the current mileage of a car.
 *
 * The Odometer class observes a Car instance and accumulates mileage
 * based on the car's speed. It derives from Meter and therefore acts as
 * a display component. Updates occur when the subject notifies this
 * meter through the Observer pattern.
 *
 * \author Simon
 * \date   November 2025
 *********************************************************************/

#ifndef ODOMETER_HPP
#define ODOMETER_HPP

#include "Object.h"
#include "Meter.hpp"
#include "Car.hpp"

 /**
  * \class Odometer
  * \brief Meter implementation that calculates and displays vehicle mileage.
  *
  * The Odometer observes a Car instance and increases its internal mileage
  * value based on the car's current speed and a fixed update interval.
  * Mileage is stored as a double for accumulation precision, but exposed
  * as a size_t when queried.
  *
  * The car pointer is stored as a weak pointer to avoid ownership cycles.
  * If the car expires, Update() throws an exception.
  */
class Odometer : public Meter {
public:

    /**
     * \brief Error message thrown when a null pointer is passed.
     */
    inline static const std::string ERROR_NULLPTR = "ERROR Nullptr";

    /**
     * \brief Update interval in milliseconds.
     *
     * This value determines how frequently the odometer expects to be
     * updated. It is used in the mileage calculation:
     *   mileage += speed_kph * (interval_ms / milliseconds_per_hour)
     */
    inline static const size_t Update_Intervall = 500;

    /**
     * \brief Shared pointer alias for Odometer.
     */
    using Sptr = std::shared_ptr<Odometer>;

    /**
     * \brief Updates the mileage and forwards the new value to the display.
     *
     * The method attempts to lock the weak pointer to the observed Car.
     * If locking fails, the method throws ERROR_NULLPTR.
     *
     * The current speed is retrieved from the Car and converted into
     * distance traveled during the update interval. The resulting mileage
     * is forwarded to the associated WindowsDisplay instance if available.
     *
     * \throws std::string ERROR_NULLPTR if the car pointer is expired.
     */
    virtual void Update() override;

    /**
     * \brief Returns the accumulated mileage.
     *
     * \return Mileage as a size_t value.
     */
    size_t GetMilage() const;

    /**
     * \brief Constructs an Odometer with a Car and a display.
     *
     * Both pointers must be non-null. The Car pointer is stored as a weak
     * reference. Display ownership is transferred via move semantics.
     *
     * \param car Shared pointer to the observed Car.
     * \param display Shared pointer to a WindowsDisplay instance.
     *
     * \throws std::string ERROR_NULLPTR if either pointer is null.
     */
    Odometer(Car::Sptr car, WindowsDisplay::SPtr display);

    /**
     * \brief Constructs an Odometer with a Car and without a display.
     *
     * The display must be set later using SetDisplay() before visual output
     * is possible.
     *
     * \param car Shared pointer to the Car being observed.
     *
     * \throws std::string ERROR_NULLPTR if car is null.
     */
    Odometer(Car::Sptr car);

private:

    /**
     * \brief Weak pointer to the observed Car.
     *
     * Ensures there is no ownership cycle between Car and Odometer.
     */
    Car::Wptr m_car;

    /**
     * \brief Accumulated mileage in kilometers (stored as double).
     *
     * Internally stored as double for precision. Exposed as size_t via
     * GetMilage() for external usage.
     */
    double m_milage;

    /**
     * \brief Number of milliseconds in one hour.
     *
     * Used for converting speed (KPH) into incremental distance
     * based on the update interval.
     */
    static const size_t mseconds_in_hours = 3600000;
};

#endif // !ODOMETER_HPP
