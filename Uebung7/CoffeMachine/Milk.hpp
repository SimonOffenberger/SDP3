#ifndef MILK_HPP
#define	MILK_HPP

#include <string>

#include "Object.h"
#include "Ingredient.hpp"

class Milk : public Ingredient {
public:

	Milk(ICoffee::Uptr cof) : Ingredient{ move(cof) } {}

	virtual double GetCost() override;

	virtual std::string GetDescription() override;

};

#endif // !MILK_HPP