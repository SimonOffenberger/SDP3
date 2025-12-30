/**
 * @file ICoffee.hpp
 * @brief Declares the abstract coffee interface for pricing and descriptions.
 */
#ifndef ICOFFEE_HPP
#define	ICOFFEE_HPP

#include <memory>
#include <string>

class ICoffee {
public:

	using Uptr = std::unique_ptr<ICoffee>;

	/**
	 * @brief Compute the total cost of the coffee including decorations.
	 * @return Final price in Euros.
	 */
	virtual double GetCost() const = 0;

	/**
	 * @brief Provide a human-readable description of the coffee order.
	 * @return Description string ending with a separator.
	 */
	virtual std::string GetDescription() const = 0;

	virtual ~ICoffee() = default;
};


#endif // !ICOFFEE_HPP