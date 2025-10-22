#include "Employee.hpp"
#include <cctype>
#include <algorithm>

Employee::Employee(
    std::string     name,
    std::string     nameID,
    TDate       dateJoined,
    TDate   dateBirth,
    std::string     socialSecurityNumber
) : m_name{ name },
m_nameIdentifier{ nameID },
m_dateJoined{ dateJoined },
m_dateBirth{ dateBirth }
//m_socialSecurityNumber{ socialSecurityNumber }
{
    if (nameID.length() != 3) throw ERROR_BAD_ID;

    if (! std::all_of(socialSecurityNumber.begin(), socialSecurityNumber.end(), ::isdigit))  throw ERROR_BAD_SOZIAL_SEC_NUM;

    if (! (socialSecurityNumber.size() == SozialSecNumLen) )  throw ERROR_BAD_SOZIAL_SEC_NUM;

    m_socialSecurityNumber = socialSecurityNumber;

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
    }

    ost << "Datenblatt\n---------------\n";
    ost << "Name: " << m_name << std::endl;
    ost << "Kuerzel: " << m_nameIdentifier << std::endl;
    ost << "Sozialversicherungsnummer: " << m_socialSecurityNumber;
    ost << m_dateBirth.day() << static_cast<unsigned>(m_dateBirth.month()) << static_cast<int>(m_dateBirth.year())%100 << std::endl;
    ost << "Geburtstag: " << m_dateBirth << std::endl;
    ost << "Einstiegsjahr: " << m_dateJoined.year() << std::endl;

    PrintSpecificData(ost);

    ost << std::endl;

    return ost;
}

