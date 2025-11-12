#ifndef METER_HPP
#define METER_HPP

#include "Object.h"
#include "IDisplay.hpp"
#include "WindowsDisplay.h"


class Meter : public Object, public IDisplay {
public:

private:
	std::unique_ptr<WindowsDisplay> m_window;
};


#endif // !METER_HPP
