#ifndef EXTENDED_ONE_HPP
#define	EXTENDED_ONE_HPP

#include "Object.h"
#include "ICoffee.hpp"


class ExtendedOne : public ICoffee, public Object {

	using Sptr = std::shared_ptr<ExtendedOne>;

	virtual double GetCost() override;

	virtual std::string GetDescription() override;

};

#endif // !EXTENDED_ONE_HPP