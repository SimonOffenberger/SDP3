/**
 * @file Espresso.hpp
 * @brief Declares the espresso coffee implementation of ICoffee.
 */
#ifndef ESPRESSO_HPP
#define	ESPRESSO_HPP

#include "Object.h"
#include "ICoffee.hpp"


class Espresso : public ICoffee , public Object {

	using Sptr = std::shared_ptr<Espresso>;

	/**
	 * @brief Return the price of an espresso.
	 */
	virtual double GetCost() override;

	/**
	 * @brief Provide the espresso description label.
	 */
	virtual std::string GetDescription() override;

};

#endif // !ESPRESSO_HPP