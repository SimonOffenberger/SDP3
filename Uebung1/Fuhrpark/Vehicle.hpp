#ifndef VEHICLE_HPP
#define VEHICLE_HPP

#include "Object.hpp"
#include "DriveRecord.hpp"

class Vehicle: public Object {
public:
	enum TFuel {
		Diesel = 0,
		Benzin = 1,
		Elektro = 2,
	};

	Vehicle(std::string brand, Vehicle::TFuel fuelType) : m_brand{ brand }, m_fuel{ fuelType } {}

	std::string GetBrand() const;

	std::string GetPlate() const;

	Vehicle::TFuel GetFuelType() const;

	const DriveRecord & GetDriveRecord() const;

	void SetPlate(std::string brand);

protected:

	Vehicle() = default;

private:
	std::string m_brand;
	std::string m_plate;
	TFuel m_fuel;
	DriveRecord m_record;
};


#endif // !1