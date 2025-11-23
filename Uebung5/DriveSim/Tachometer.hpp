/*****************************************************************//**
 * \file   Tachometer.hpp
 * \brief  Display that shows the current speed of a car.
 *
 * The Tachometer observes a Car instance and displays its current speed.
 * It derives from Meter and serves as an observer in the Vehicle system.
 *
 * \author Simon
 * \date   November 2025
 *********************************************************************/

#ifndef TACHOMETER_HPP
#define TACHOMETER_HPP

#include "Object.h"
#include "Meter.hpp"
#include "Car.hpp"

 /**
  * \class Tachometer
  * \brief Meter implementation that displays the real-time speed of a vehicle.
  */
class Tachometer : public Meter {
public:

    /**
     * \brief Error message thrown when a null pointer is passed.
     */
    inline static const std::string ERROR_NULLPTR = "ERROR Nullptr";

    /**
     * \brief Shared pointer alias for Tachometer.
     */
    using Sptr = std::shared_ptr<Tachometer>;

    /**
     * \brief Updates the tachometer display with the current speed.
     *
     *
     * \throws std::string ERROR_NULLPTR if the car pointer is expired.
     */
    virtual void Update() override;

    /**
     * \brief Constructs a Tachometer with both a Car and a display.
     *
     * \param car Shared pointer to the observed Car.
     * \param display Shared pointer to a WindowsDisplay instance.
     *
     * \throws std::string ERROR_NULLPTR if car or display is null.
     */
    Tachometer(Car::Sptr car, WindowsDisplay::SPtr display);

    /**
     * \brief Constructs a Tachometer with a Car but without a display.
     *
     * A valid display can be attached later using SetDisplay(), inherited
     * from Meter. The Car pointer must not be null and is stored as a
     * weak pointer.
     *
     * \param car Shared pointer to the observed Car.
     *
     * \throws std::string ERROR_NULLPTR if car is null.
     */
    Tachometer(Car::Sptr car);

private:

    /**
     * \brief Weak pointer to the observed Car.
     *
     * Prevents ownership cycles between Car and Tachometer. If the Car
     * instance is destroyed, Update() will detect this via lock().
     */
    Car::Wptr m_car;

    /**
     * \brief Last measured speed in kilometers per hour.
     *
     * This value is updated during each call to Update() and forwarded
     * to the WindowsDisplay using SendValue().
     */
    double m_speed;
};

#endif // !TACHOMETER_HPP
