/*****************************************************************//**
 * \file   PieceWorker.cpp
 * \brief  PieceWorker Class - inherits from Employee
 * \author Simon Vogelhuber
 * \date   October 2025
 *********************************************************************/
#include "PieceWorker.hpp"

PieceWorker::PieceWorker(
    const std::string & name,
    const std::string & nameID,
    const TDate & dateJoined,
    const TDate & dateBirth,
    const std::string & socialSecurityNumber,
    const size_t & m_numberPieces,
    const size_t & m_commisionPerPiece
) :
    Employee(name, nameID, dateJoined, dateBirth, socialSecurityNumber),
    m_numberPieces{ m_numberPieces },
    m_commisionPerPiece{ m_commisionPerPiece }{}

std::ostream& PieceWorker::DoPrintSpecificData(std::ostream& ost) const
{
    if (ost.bad())
    {
        throw Object::ERROR_BAD_OSTREAM;
        return ost;
    }
    ost << "Role: PieceWorker" << std::endl;
    ost << "Pieces produced: " << m_numberPieces << std::endl;
    ost << "Pay per piece: " << m_commisionPerPiece << " EUR" << std::endl;

    return ost; 
}

size_t PieceWorker::GetProducedItems() const
{
    return m_numberPieces;
}

size_t PieceWorker::GetSalary() const
{
    return m_numberPieces * m_commisionPerPiece;
}

TWorker PieceWorker::GetWorkerType() const
{
    return E_PieceWorker;
}

Employee* PieceWorker::Clone() const
{
    return new PieceWorker{ *this };
}
