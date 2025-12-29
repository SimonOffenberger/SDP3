/**
 * @file Espresso.hpp
 * @brief Declares the espresso coffee implementation of ICoffee.
 */
#ifndef ESPRESSO_HPP
#define	ESPRESSO_HPP

#include "Object.h"
#include "ICoffee.hpp"


class Espresso : public ICoffee , public Object {
public:

	using Sptr = std::shared_ptr<Espresso>;

	Espresso() = default;

	/**
	 * @brief Return the price of an espresso.
	 */
	virtual double GetCost() override;

	/**
	 * @brief Provide the espresso description label.
	 */
	virtual std::string GetDescription() override;


	// explicitly delete Assign Op and Copy Ctor to prevent untestet behaviour
	void operator=(Espresso& ind) = delete;
	Espresso(Espresso& ind) = delete;
};

#endif // !ESPRESSO_HPP