#ifndef CREAM_HPP
#define	CREAM_HPP

#include <string>

#include "Object.h"
#include "Ingredient.hpp"

class Cream : public Ingredient {
public:

	Cream(ICoffee::Uptr cof) : Ingredient{ move(cof) } {}

	virtual double GetCost() override;

	virtual std::string GetDescription() override;

};

#endif // !CREAM_HPP