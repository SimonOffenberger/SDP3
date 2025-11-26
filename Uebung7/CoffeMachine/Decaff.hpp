#ifndef DECAFF_HPP
#define	DECAFF_HPP

#include "Object.h"
#include "ICoffee.hpp"

class Decaff : public ICoffee, public Object {

	using Sptr = std::shared_ptr<Decaff>;

	virtual double GetCost() override;

	virtual std::string GetDescription() override;

};

#endif // !DECAFF_HPP