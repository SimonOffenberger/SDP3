/*****************************************************************//**
 * \file   Boss.cpp
 * \brief  Boss Class - inherits from Employee
 * \author Simon Vogelhuber
 * \date   October 2025
 *********************************************************************/
#include "Boss.hpp"

Boss::Boss(
    const std::string & name, 
    const std::string & nameID, 
    const TDate & dateJoined,
    const TDate & dateBirth,
    const std::string & socialSecurityNumber,
    const size_t & salary
) :
    Employee(name, nameID, dateJoined, dateBirth, socialSecurityNumber),
    m_salary{ salary } {}

std::ostream& Boss::DoPrintSpecificData(std::ostream& ost) const
{
    if (ost.bad())
    {
        throw Object::ERROR_BAD_OSTREAM;
        return ost;
    }
    ost << "Role: Boss" << std::endl;
    ost << "Salary: " << m_salary << " EUR" << std::endl;

    return ost;
}

size_t Boss::GetSalary() const
{
    return m_salary;
}

TWorker Boss::GetWorkerType() const
{
    return E_Boss;
}

Employee* Boss::Clone() const
{
    return new Boss{ *this };
}
