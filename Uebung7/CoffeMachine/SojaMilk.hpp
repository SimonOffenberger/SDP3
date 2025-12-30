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
	virtual double GetCost() const override;

	/**
	 * @brief Append soja milk label to description.
	 */
	virtual std::string GetDescription() const override;

	// explicitly delete Assign Op and Copy Ctor to prevent untestet behaviour
	void operator=(SojaMilk& ind) = delete;
	SojaMilk(SojaMilk& ind) = delete;
};

#endif // !SOJA_MILK_HPP