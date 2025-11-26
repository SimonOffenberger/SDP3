#ifndef SOJA_MILK_HPP
#define	SOJA_MILK_HPP

#include <string>

#include "Object.h"
#include "Ingredient.hpp"

class SojaMilk : public Ingredient {
public:

	SojaMilk(ICoffee::Uptr cof) : Ingredient{ move(cof) } {}

	virtual double GetCost() override;

	virtual std::string GetDescription() override;

};

#endif // !SOJA_MILK_HPP