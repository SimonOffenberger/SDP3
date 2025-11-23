/*****************************************************************//**
 * \file   Vehicle.hpp
 * \brief  Base class representing a generic vehicle that supports
 *         display observers following the Observer design pattern.
 *
 * The Vehicle class manages a collection of display observers that
 * implement the IDisplay interface. Observers can be attached or
 * detached at runtime.
 *
 * \author Simon
 * \date   November 2025
 *********************************************************************/

#ifndef VEHICLE_HPP
#define VEHICLE_HPP

#include "Object.h"
#include "IDisplay.hpp"
#include <vector>

 /**
  * \class Vehicle
  * \brief Base class supporting observer management for display updates.
  */
class Vehicle : public Object {
public:

    /**
     * \brief Error message thrown when a null pointer is passed.
     */
    inline static const std::string ERROR_NULLPTR = "ERROR Nullptr";

    /**
     * \brief Container type alias for display observers.
     *
     * Stores shared pointers to IDisplay implementations.
     */
    using TCont = std::vector<IDisplay::Sptr>;

    /**
     * \brief Attaches a display observer to the vehicle.
     *
     * \param display Shared pointer to a display object implementing IDisplay.
     *
     * \throws std::string ERROR_NULLPTR if display is null.
     */
    void Attach(IDisplay::Sptr display);

    /**
     * \brief Detaches a display observer from the vehicle.
     *
     * \param display Shared pointer to a display object that should be removed.
     *
     * \throws std::string ERROR_NULLPTR if display is null.
     */
    void Detach(IDisplay::Sptr display);

protected:

    /**
     * \brief Notifies all attached display observers.
     *
     * This method loops through all observers stored in the container and
     * calls Update() on each non-null display.
     */
    void Notify() const;

    /**
     * \brief Protected default constructor.
     *
     * Prevents direct instantiation of Vehicle, as it should be subclassed.
     */
    Vehicle() = default;

private:

    /**
     * \brief Container holding all attached display observers.
     */
    TCont m_display_observers;
};

#endif // !VEHICLE_HPP
