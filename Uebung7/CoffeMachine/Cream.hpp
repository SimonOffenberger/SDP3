/**
 * @file Cream.hpp
 * @brief Declares the cream ingredient decorator for coffee orders.
 */
#ifndef CREAM_HPP
#define	CREAM_HPP

#include <string>

#include "Object.h"
#include "Ingredient.hpp"

class Cream : public Ingredient {
public:

	/**
	 * @brief Wrap a coffee with cream.
	 * @param cof Coffee to decorate.
	 */
	Cream(ICoffee::Uptr cof) : Ingredient{ move(cof) } {}

	/**
	 * @brief Return price including cream surcharge.
	 */
	virtual double GetCost() override;

	/**
	 * @brief Append cream label to description.
	 */
	virtual std::string GetDescription() override;

};

#endif // !CREAM_HPP