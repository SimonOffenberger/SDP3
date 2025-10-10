#include "Vehicle.hpp"

std::string Vehicle::GetBrand() const
{
    return m_brand;
}

std::string Vehicle::GetPlate() const
{
    return m_plate;
}

Vehicle::TFuel Vehicle::GetFuelType() const
{
    return m_fuel;
}

const DriveRecord & Vehicle::GetDriveRecord() const
{
    return m_record;
}

void Vehicle::SetPlate(std::string brand)
{
    m_plate = brand;
}

