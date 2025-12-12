/**
 * @file Mocha.hpp
 * @brief Declares the mocha coffee implementation of ICoffee.
 */
#ifndef MOCHA_HPP
#define	MOCHA_HPP

#include "Object.h"
#include "ICoffee.hpp"


class Mocha : public ICoffee, public Object {

	using Sptr = std::shared_ptr<Mocha>;

	/**
	 * @brief Return the price of a mocha.
	 */
	virtual double GetCost() override;

	/**
	 * @brief Provide the mocha description label.
	 */
	virtual std::string GetDescription() override;

};

#endif // !MOCHA_HPP