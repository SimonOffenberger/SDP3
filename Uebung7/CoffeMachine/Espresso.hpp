#ifndef ESPRESSO_HPP
#define	ESPRESSO_HPP

#include "Object.h"
#include "ICoffee.hpp"


class Espresso : public ICoffee , public Object {

	using Sptr = std::shared_ptr<Espresso>;

	virtual double GetCost() override;

	virtual std::string GetDescription() override;

};

#endif // !ESPRESSO_HPP