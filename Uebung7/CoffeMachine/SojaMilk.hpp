/**
 * @file SojaMilk.hpp
 * @brief Declares the soja milk ingredient decorator for coffee orders.
 */
#ifndef SOJA_MILK_HPP
#define	SOJA_MILK_HPP

#include <string>

#include "Object.h"
#include "Ingredient.hpp"

class SojaMilk : public Ingredient {
public:

	/**
	 * @brief Wrap a coffee with soja milk.
	 * @param cof Coffee to decorate.
	 */
	SojaMilk(ICoffee::Uptr cof) : Ingredient{ move(cof) } {}

	/**
	 * @brief Return price including soja milk surcharge.
	 */
	virtual double GetCost() override;

	/**
	 * @brief Append soja milk label to description.
	 */
	virtual std::string GetDescription() override;

};

#endif // !SOJA_MILK_HPP