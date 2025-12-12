/**
 * @file Decaff.hpp
 * @brief Declares the decaffeinated coffee implementation of ICoffee.
 */
#ifndef DECAFF_HPP
#define	DECAFF_HPP

#include "Object.h"
#include "ICoffee.hpp"

class Decaff : public ICoffee, public Object {

	using Sptr = std::shared_ptr<Decaff>;

	/**
	 * @brief Return the price of a decaffeinated coffee.
	 */
	virtual double GetCost() override;

	/**
	 * @brief Provide the decaff description label.
	 */
	virtual std::string GetDescription() override;

};

#endif // !DECAFF_HPP