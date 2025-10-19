#include "ComissionWorker.hpp"

ComissionWorker::ComissionWorker(
    std::string name,
    std::string nameID,
    TDate dateJoined,
    TDate dateBirth,
    std::string socialSecurityNumber,
    size_t baseSalary,
    size_t commisionPerPiece,
    size_t piecesSold
) :
    Employee(name, nameID, dateJoined, dateBirth, socialSecurityNumber),
    m_baseSalary{ baseSalary },
    m_commisionPerPiece{ commisionPerPiece },
    m_piecesSold { piecesSold }
{}

std::ostream& ComissionWorker::PrintSpecificData(std::ostream & ost) const
{
    if (ost.bad())
    {
        throw Object::ERROR_BAD_OSTREAM;
        return ost;
    }

    ost << "Base salary: " << m_baseSalary<< std::endl;
    ost << "Comission per piece: " << m_commisionPerPiece << std::endl;
    ost << "Pieces sold: " << m_piecesSold << std::endl;

    return ost;
}

size_t ComissionWorker::GetSoldItems() const
{
    return m_piecesSold;
}

size_t ComissionWorker::GetSalary() const
{
    return m_baseSalary + m_piecesSold * m_commisionPerPiece;
}

TWorker ComissionWorker::GetWorkerType() const
{
    return E_CommisionWorker;
}

Employee* ComissionWorker::Clone() const
{
    return new ComissionWorker{ *this };
}
