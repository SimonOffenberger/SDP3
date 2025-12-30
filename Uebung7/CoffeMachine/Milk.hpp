/**
 * @file Milk.hpp
 * @brief Declares the milk ingredient decorator for coffee orders.
 */
#ifndef MILK_HPP
#define	MILK_HPP

#include <string>

#include "Object.h"
#include "Ingredient.hpp"

class Milk : public Ingredient {
public:

	/**
	 * @brief Wrap a coffee with milk.
	 * @param cof Coffee to decorate.
	 */
	Milk(ICoffee::Uptr cof) : Ingredient{ move(cof) } {}

	/**
	 * @brief Return price including milk surcharge.
	 */
	virtual double GetCost() const override;

	/**
	 * @brief Append milk label to description.
	 */
	virtual std::string GetDescription() const override;

	// explicitly delete Assign Op and Copy Ctor to prevent untestet behaviour
	void operator=(Milk& ind) = delete;
	Milk(Milk& ind) = delete;
};

#endif // !MILK_HPP