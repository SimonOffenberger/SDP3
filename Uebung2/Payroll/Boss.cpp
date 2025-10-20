#include "Boss.hpp"

Boss::Boss(
    std::string name, 
    std::string nameID, 
    TDate dateJoined, 
    TDate dateBirth, 
    std::string socialSecurityNumber, 
    size_t salary
) :
    Employee(name, nameID, dateJoined, dateBirth, socialSecurityNumber),
    m_salary{ salary } {}

std::ostream& Boss::PrintSpecificData(std::ostream& ost) const
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
