/*****************************************************************//**
 * \file   HourlyWorker.hpp
 * \brief
 *
 * \author Simon
 * \date   October 2025
 *********************************************************************/
#include "HourlyWorker.hpp"

HourlyWorker::HourlyWorker(
    std::string name,
    std::string nameID,
    TDate dateJoined,
    TDate dateBirth,
    std::string socialSecurityNumber,
    size_t hourlyRate,
    size_t workedHours
) : 
    Employee(name, nameID, dateJoined, dateBirth, socialSecurityNumber), 
    m_hourlyRate{ hourlyRate },
    m_workedHours{ workedHours }
{}

std::ostream& HourlyWorker::PrintSpecificData(std::ostream& ost) const
{
    if (ost.bad())
    {
        throw Object::ERROR_BAD_OSTREAM;
        return ost;
    }
    ost << "Role: HourlyWWorker" << std::endl;
    ost << "Hourly rate: " << m_hourlyRate << " EUR" << std::endl;
    ost << "Hours worked: " << m_workedHours << " EUR" << std::endl;

    return ost;
}

size_t HourlyWorker::GetSalary() const
{
    return m_hourlyRate * m_workedHours;
}

TWorker HourlyWorker::GetWorkerType() const
{
    return E_HourlyWorker;
}

Employee* HourlyWorker::Clone() const
{
    return new HourlyWorker{*this};
}
