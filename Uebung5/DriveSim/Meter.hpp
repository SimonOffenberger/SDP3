/*****************************************************************//**
 * \file   Meter.hpp
 * \brief  Abstract base class for all meters
 *
 * \author Simon
 * \date   November 2025
 *********************************************************************/

#ifndef METER_HPP
#define METER_HPP

#include "Object.h"
#include "IDisplay.hpp"
#include "WindowsDisplay.h"

class Meter : public Object, public IDisplay {
public:
	/**
     * \brief Update the display with new values
	 */
	void Update() = 0;

protected:

	Meter(WindowsDisplay::SPtr display);
	
	WindowsDisplay::SPtr m_window;

private:

};


#endif // !METER_HPP
