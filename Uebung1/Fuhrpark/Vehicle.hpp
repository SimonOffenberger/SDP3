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

	std::string GetBrand() const;

	std::string GetPlate() const;

	TFuel GetFuelType() const;

	DriveRecord GetDriveRecord() const;

	void SetPlate(std::string brand);

protected:

	Vehicle() = default;

private:
	std::string m_brand;
	std::string m_plate;
	TFuel m_fuel;
};


#endif // !1