#ifndef MOCHA_HPP
#define	MOCHA_HPP

#include "Object.h"
#include "ICoffee.hpp"


class Mocha : public ICoffee, public Object {

	using Sptr = std::shared_ptr<Mocha>;

	virtual double GetCost() override;

	virtual std::string GetDescription() override;

};

#endif // !MOCHA_HPP