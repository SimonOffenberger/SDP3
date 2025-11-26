#ifndef SUGAR_HPP
#define	SUGAR_HPP

#include <string>

#include "Object.h"
#include "Ingredient.hpp"

class Sugar : public Ingredient {
public:

	Sugar(ICoffee::Uptr cof) : Ingredient{ move(cof) } {}

	virtual double GetCost() override;

	virtual std::string GetDescription() override;

};

#endif // !SUGAR_HPP