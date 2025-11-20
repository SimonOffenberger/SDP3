/*****************************************************************//**
 * \file   Meter.hpp
 * \brief  Abstract base class for all meter display types.
 *
 * The Meter class acts as a display component in the Observer pattern.
 * It derives from IDisplay and represents a meter that visualizes data
 * using a WindowsDisplay instance. Concrete meter types update their
 * visual output when Update() is called by the observed subject.
 *
 * \author Simon
 * \date   November 2025
 *********************************************************************/

#ifndef METER_HPP
#define METER_HPP

#include "Object.h"
#include "IDisplay.hpp"
#include "WindowsDisplay.h"

 /**
  * \class Meter
  * \brief Abstract base class for all meter display components.
  *
  * The Meter class provides the foundation for visual display elements
  * that react to state changes from a subject (for example, a Vehicle).
  * It maintains a WindowsDisplay instance used for rendering.
  *
  * Display pointers are stored using move semantics. Null pointers are
  * not permitted and will result in an exception. Subclasses should rely
  * on the protected member m_window when performing drawing operations.
  */
class Meter : public Object, public IDisplay {
public:

    /**
     * \brief Error message thrown when a null pointer is passed.
     */
    inline static const std::string ERROR_NULLPTR = "ERROR Nullptr";

    /**
     * \brief Sets the WindowsDisplay instance used by this meter.
     *
     * The provided pointer must not be null. The display pointer is moved
     * into internal storage, transferring ownership to the Meter object.
     * Existing display pointers (if any) are overwritten.
     *
     * \param display Shared pointer to a WindowsDisplay.
     *
     * \throws std::string ERROR_NULLPTR if display is null.
     */
    void SetDisplay(WindowsDisplay::SPtr display);

protected:

    /**
     * \brief Constructs a Meter with an initial WindowsDisplay instance.
     *
     * The provided display pointer must not be null. Ownership of the
     * pointer is transferred into the Meter through move semantics.
     * Derived meter classes typically call this constructor to ensure
     * that drawing capabilities are available immediately.
     *
     * \param display Shared pointer to a WindowsDisplay.
     *
     * \throws std::string ERROR_NULLPTR if display is null.
     */
    Meter(WindowsDisplay::SPtr display);

    /**
     * \brief Default protected constructor.
     *
     * Allows derived classes to be created without immediately providing
     * a display. A valid display must later be set through SetDisplay().
     */
    Meter() = default;

    /**
     * \brief Pointer to the display window used by the meter.
     *
     * This pointer is assigned through either the constructor or
     * SetDisplay(), using move semantics. Derived classes use this
     * member for rendering updated values.
     */
    WindowsDisplay::SPtr m_window;

private:
    // No private members currently required.
};

#endif // !METER_HPP
