#include "Employee.hpp"

Employee::Employee(
    std::string     name,
    std::string     nameID,
    TDate       dateJoined,
    TDate   dateBirth,
    std::string     socialSecurityNumber
) : m_name{ name },
m_nameIdentifier{ nameID },
m_dateJoined{ dateJoined },
m_dateBirth{ dateBirth },
m_socialSecurityNumber{ socialSecurityNumber }
{
    if (nameID.length() != 3)
        throw ERROR_BAD_ID;
}

std::string Employee::GetID() const
{
    return m_nameIdentifier;
}

TDate Employee::GetDateBirth() const
{
    return m_dateBirth;
}

TDate Employee::GetDateJoined() const
{
    return m_dateJoined;
}

std::ostream& Employee::PrintDatasheet(std::ostream& ost) const
{
    if (ost.bad())
    {
        throw Object::ERROR_BAD_OSTREAM;
        return ost;
    }

    ost << "Datenblatt\n---------------\n";
    ost << "Name: " << m_name << std::endl;
    ost << "Kürzel: " << m_nameIdentifier << std::endl;
    ost << "Sozialversicherungsnummer: " << m_socialSecurityNumber << std::endl;
    ost << "Geburtstag: " << m_dateBirth << std::endl;
    ost << "Einstiegsjahr: " << m_dateJoined.year() << std::endl;

    PrintSpecificData(ost);

    return ost;
}
