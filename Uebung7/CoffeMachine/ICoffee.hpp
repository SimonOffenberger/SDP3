#ifndef ICOFFEE_HPP
#define	ICOFFEE_HPP

#include <memory>

class ICoffee {
public:

	using Uptr = std::unique_ptr<ICoffee>;

	virtual double GetCost() = 0;

	virtual std::string GetDescription() = 0;

	virtual ~ICoffee() = default;
};




#endif // !ICOFFEE_HPP