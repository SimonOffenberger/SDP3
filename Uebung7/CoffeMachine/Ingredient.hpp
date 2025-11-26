#ifndef INGREDIENT_HPP
#define	INGREDIENT_HPP

#include "Object.h"
#include "ICoffee.hpp"

class Ingredient : public ICoffee , public Object {
public:


	virtual double GetCost() override;

	virtual std::string GetDescription() override;

protected:

	Ingredient(ICoffee::Uptr mCoffeeIngredient);

	ICoffee::Uptr mDecorator;
};


#endif // !INGREDIENT_HPP