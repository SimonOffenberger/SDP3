/**
 * @file ExtendedOne.hpp
 * @brief Declares the extended coffee variant implementation of ICoffee.
 */
#ifndef EXTENDED_ONE_HPP
#define	EXTENDED_ONE_HPP

#include "Object.h"
#include "ICoffee.hpp"


class ExtendedOne : public ICoffee, public Object {
public:

	using Uptr = std::unique_ptr<ExtendedOne>;

	ExtendedOne() = default;

	/**
	 * @brief Return the price of the extended variant.
	 */
	virtual double GetCost() const override;

	/**
	 * @brief Provide the extended variant description label.
	 */
	virtual std::string GetDescription() const override;

	// explicitly delete Assign Op and Copy Ctor to prevent untestet behaviour
	void operator=(ExtendedOne& ind) = delete;
	ExtendedOne(ExtendedOne& ind) = delete;
};

#endif // !EXTENDED_ONE_HPP