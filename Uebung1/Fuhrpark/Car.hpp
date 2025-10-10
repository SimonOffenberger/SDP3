#ifndef CAR_HPP
#define CAR_HPP

#include "Vehicle.hpp"

class Car : public Vehicle {
public:

	Car(const std::string & brand,const TFuel & fuelType) : Vehicle(brand, fuelType) {}

	virtual std::ostream& Print(std::ostream& ost = std::cout) const override;

private:
};


#endif // !1