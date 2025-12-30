/**
 * @file Decaff.hpp
 * @brief Declares the decaffeinated coffee implementation of ICoffee.
 */
#ifndef DECAFF_HPP
#define	DECAFF_HPP

#include "Object.h"
#include "ICoffee.hpp"

class Decaff : public ICoffee, public Object {
public:

	using Uptr = std::unique_ptr<Decaff>;

	Decaff() = default;


	/**
	 * @brief Return the price of a decaffeinated coffee.
	 */
	virtual double GetCost() const override;

	/**
	 * @brief Provide the decaff description label.
	 */
	virtual std::string GetDescription() const override;

	// explicitly delete Assign Op and Copy Ctor to prevent untestet behaviour
	void operator=(Decaff& ind) = delete;
	Decaff(Decaff& ind) = delete;

};

#endif // !DECAFF_HPP