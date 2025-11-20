/*****************************************************************//**
 * \file   IDisplay.hpp
 * \brief  Interface for all display types used by vehicles.
 *
 * The IDisplay interface represents any output or visualization component
 * that can receive update notifications from a vehicle. It is designed to
 * be used with the Observer design pattern. Implementations must override
 * the Update() function to react to state changes.
 *
 * \author Simon
 * \date   November 2025
 *********************************************************************/

#ifndef IDISPLAY_HPP
#define IDISPLAY_HPP

#include <memory>

 /**
  * \class IDisplay
  * \brief Interface for display observer implementations.
  *
  * The IDisplay class defines the contract for any display that observes
  * a vehicle. When the vehicle's state changes, the Vehicle class calls
  * Update() on all attached observers. Classes implementing this interface
  * must provide the Update() behavior appropriate for their display type.
  */
class IDisplay {
public:

    /**
     * \brief Shared pointer alias for IDisplay.
     */
    using Sptr = std::shared_ptr<IDisplay>;

    /**
     * \brief Called when the observed subject updates its state.
     *
     * This method is invoked by the Vehicle class through its Notify()
     * function. Implementations must override this method to update their
     * displayed information.
     */
    virtual void Update() = 0;

    /**
     * \brief Virtual destructor.
     *
     * Ensures proper cleanup of derived display types.
     */
    virtual ~IDisplay() = default;

protected:

    /**
     * \brief Protected default constructor.
     *
     * Prevents direct instantiation of the interface and enforces
     * implementation through derived classes.
     */
    IDisplay() = default;
};

#endif // !IDISPLAY_HPP
