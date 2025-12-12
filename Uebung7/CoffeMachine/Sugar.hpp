/**
 * @file Sugar.hpp
 * @brief Declares the sugar ingredient decorator for coffee orders.
 */
#ifndef SUGAR_HPP
#define	SUGAR_HPP

#include <string>

#include "Object.h"
#include "Ingredient.hpp"

class Sugar : public Ingredient {
public:

	/**
	 * @brief Wrap a coffee with sugar.
	 * @param cof Coffee to decorate.
	 */
	Sugar(ICoffee::Uptr cof) : Ingredient{ move(cof) } {}

	/**
	 * @brief Return price including sugar surcharge.
	 */
	virtual double GetCost() override;

	/**
	 * @brief Append sugar label to description.
	 */
	virtual std::string GetDescription() override;

};

#endif // !SUGAR_HPP