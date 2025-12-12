/**
 * @file Ingredient.hpp
 * @brief Declares the decorator base class that augments an ICoffee.
 */
#ifndef INGREDIENT_HPP
#define	INGREDIENT_HPP

#include "Object.h"
#include "ICoffee.hpp"

class Ingredient : public ICoffee , public Object {
public:
	inline static const std::string ERROR_NULLPTR = "Error Nullptr!";

	/**
	 * @brief Forward cost request to the decorated coffee.
	 * @return Accumulated coffee price.
	 */
	virtual double GetCost() override;

	/**
	 * @brief Forward description request to the decorated coffee.
	 * @return Aggregated description string.
	 */
	virtual std::string GetDescription() override;

protected:

	/**
	 * @brief Construct a decorator around another coffee.
	 * @param mCoffeeIngredient Coffee instance to wrap; must not be null.
	 */
	Ingredient(ICoffee::Uptr mCoffeeIngredient);

	ICoffee::Uptr mDecorator;
};


#endif // !INGREDIENT_HPP