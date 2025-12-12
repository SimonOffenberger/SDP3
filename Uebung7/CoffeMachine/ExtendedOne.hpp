/**
 * @file ExtendedOne.hpp
 * @brief Declares the extended coffee variant implementation of ICoffee.
 */
#ifndef EXTENDED_ONE_HPP
#define	EXTENDED_ONE_HPP

#include "Object.h"
#include "ICoffee.hpp"


class ExtendedOne : public ICoffee, public Object {

	using Sptr = std::shared_ptr<ExtendedOne>;

	/**
	 * @brief Return the price of the extended variant.
	 */
	virtual double GetCost() override;

	/**
	 * @brief Provide the extended variant description label.
	 */
	virtual std::string GetDescription() override;

};

#endif // !EXTENDED_ONE_HPP