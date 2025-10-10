#ifndef VEHICLE_HPP
#define VEHICLE_HPP

#include "Object.hpp"
#include "DriveRecord.hpp"

enum TFuel {
	Diesel = 0,
	Benzin = 1,
	Elektro = 2,
};

class Vehicle: public Object {
public:

	std::string GetBrand() const;

	std::string GetPlate() const;

	TFuel GetFuelType() const;

	const DriveRecord & GetDriveRecord() const;

	void SetPlate(const std::string & brand);

	void AddRecord(const RecordEntry& entry);

	size_t Get_Milage() const;

protected:

	Vehicle(const std::string & brand,const TFuel & fuelType) : m_brand{ brand }, m_fuel{ fuelType } {}

private:
	std::string m_brand;
	std::string m_plate;
	TFuel m_fuel;
	DriveRecord m_record;
};


#endif // !1