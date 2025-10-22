/*****************************************************************//**
 * \file   PieceWorker.hpp
 * \brief  
 * 
 * \author Simon
 * \date   October 2025
 *********************************************************************/
#ifndef PIECE_WORKER_H
#define PIECE_WORKER_H

#include "Employee.hpp"

class PieceWorker : public Employee
{
public:


    PieceWorker(
        std::string name,
        std::string nameID,
        TDate dateJoined,
        TDate dateBirth,
        std::string socialSecurityNumber,
        size_t m_numberPieces,
        size_t m_commisionPerPiece
    );


    /**
     * \brief Returns the number of pieces the
     * worker has produced
     */
    size_t GetProducedItems() const override;

    /**
     * \brief Just here because of whacky class structure.
     * Worker does not strictly sell items!
     */
    size_t GetSoldItems() const override { return 0; };

    /**
    * \brief Returns the total earnings for an
    * worker in this month.
    * \return size_t
    */
    size_t GetSalary() const override;

    /**
     * \brief Returns the type of worker.
     * \return TWorker
     */
    TWorker GetWorkerType() const override;

    /**
     * \brief Creates a clone on the Heap
     * and returns a pointer.
     * \return Employee*
     */
    Employee* Clone() const override;

protected:
    /**
     * \brief Prints worker specific information
     * \param std::ostream& ost
     * \return std::ostream&
     */
    std::ostream& PrintSpecificData(std::ostream& ost) const override;

private:
    size_t m_numberPieces;
    size_t m_commisionPerPiece;
};

#endif // !PIECE_WORKER_H