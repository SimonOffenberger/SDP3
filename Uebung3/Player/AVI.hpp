#ifndef AVI_HPP
#define AVI_HPP

#include "Object.hpp"
#include "IVideoFormat.hpp"
#include <iostream>

class AVI : public Object, public IVideoformat
{
public:
	virtual void Print(std::ostream & ost) const override;
};

#endif // !define AVI_HPP