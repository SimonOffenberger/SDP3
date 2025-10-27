#ifndef WMV_HPP
#define WMV_HPP

#include "Object.hpp"
#include "IVideoFormat.hpp"
#include <iostream>

class WMV : public Object, public IVideoformat
{
public:
	virtual void Print(std::ostream& ost) const override;
};

#endif // !define MKV_HPP