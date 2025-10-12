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

void Vehicle::SetPlate(const std::string & plate)
{
    m_plate = plate;
}

void Vehicle::AddRecord(const RecordEntry& entry)
{
    m_record.AddRecord(entry);
}

size_t Vehicle::GetMilage() const
{
    return m_record.GetMilage();
}


