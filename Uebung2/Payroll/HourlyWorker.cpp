/*****************************************************************//**
 * \file   HourlyWorker.cpp
 * \brief  HourlyWorker Class - Inherits from Employee
 * \author Simon
 * \date   October 2025
 *********************************************************************/

#include "HourlyWorker.hpp"

HourlyWorker::HourlyWorker(
    const std::string & name,
    const std::string & nameID,
    const TDate & dateJoined,
    const TDate & dateBirth,
    const std::string & socialSecurityNumber,
    const size_t & hourlyRate,
    const size_t & workedHours
) : 
    Employee(name, nameID, dateJoined, dateBirth, socialSecurityNumber), 
    m_hourlyRate{ hourlyRate },
    m_workedHours{ workedHours }
{}

std::ostream& HourlyWorker::DoPrintSpecificData(std::ostream& ost) const
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
