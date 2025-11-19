#ifndef METER_HPP
#define METER_HPP

#include "Object.h"
#include "IDisplay.hpp"
#include "WindowsDisplay.h"


class Meter : public Object, public IDisplay {
public:

	void Update() = 0;

protected:

	Meter(WindowsDisplay::SPtr display);
	
	WindowsDisplay::SPtr m_window;

private:

};


#endif // !METER_HPP
