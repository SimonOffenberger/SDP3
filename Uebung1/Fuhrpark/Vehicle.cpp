#include "Vehicle.hpp"

std::string Vehicle::GetBrand() const
{
    return m_brand;
}

std::string Vehicle::GetPlate() const
{
    return m_plate;
}

TFuel Vehicle::GetFuelType() const
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

void Vehicle::AddRecord(const RecordEntry& entry)
{
    m_record.AddRecord(entry);
}

