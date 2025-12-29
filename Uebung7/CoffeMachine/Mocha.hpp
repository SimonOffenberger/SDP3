/**
 * @file Mocha.hpp
 * @brief Declares the mocha coffee implementation of ICoffee.
 */
#ifndef MOCHA_HPP
#define	MOCHA_HPP

#include "Object.h"
#include "ICoffee.hpp"


class Mocha : public ICoffee, public Object {
public:

	Mocha() = default;


	/**
	 * @brief Return the price of a mocha.
	 */
	virtual double GetCost() override;

	/**
	 * @brief Provide the mocha description label.
	 */
	virtual std::string GetDescription() override;

	// explicitly delete Assign Op and Copy Ctor to prevent untestet behaviour
	void operator=(Mocha& ind) = delete;
	Mocha(Mocha& ind) = delete;
};

#endif // !MOCHA_HPP