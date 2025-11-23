/*****************************************************************//**
 * \file   Meter.hpp
 * \brief  Abstract base class for all meter display types.
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
  */
class Meter : public Object, public IDisplay {
public:

    /**
     * \brief Error message thrown when a null pointer is passed.
     */
    inline static const std::string ERROR_NULLPTR = "ERROR Nullptr";

    /**
     * \brief Sets the WindowsDisplay instance used by this meter.
     * \param display Shared pointer to a WindowsDisplay.
     *
     * \throws std::string ERROR_NULLPTR if display is null.
     */
    void SetDisplay(WindowsDisplay::SPtr display);

protected:

    /**
     * \brief Constructs a Meter with an initial WindowsDisplay instance.
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
     */
    WindowsDisplay::SPtr m_window;

private:
    // No private members currently required.
};

#endif // !METER_HPP
