#ifndef MKV_HPP
#define MKV_HPP

#include "Object.hpp"
#include "IVideoFormat.hpp"
#include <iostream>

class MKV : public Object, public IVideoformat
{
public:
	virtual void Print(std::ostream& ost) const override;
};

#endif // !define MKV_HPP