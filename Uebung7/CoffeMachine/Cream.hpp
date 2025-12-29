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

	using Uptr = std::unique_ptr<Cream>;


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

	// explicitly delete Assign Op and Copy Ctor to prevent untestet behaviour
	void operator=(Cream& ind) = delete;
	Cream(Cream& ind) = delete;

};

#endif // !CREAM_HPP