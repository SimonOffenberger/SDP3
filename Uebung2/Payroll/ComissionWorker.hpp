#ifndef COMISSION_WORKER_H
#define COMISSION_WORKER_H

#include "Employee.hpp"

class ComissionWorker : public Employee
{
public:

    ComissionWorker(
        std::string name,
        std::string nameID,
        TDate dateJoined,
        TDate dateBirth,
        std::string socialSecurityNumber,
        size_t baseSalary,
        size_t commisionPerPiece,
        size_t piecesSold
    );

    /**
     * \brief Just here because of whacky class structure.
     * Worker does not strictly produce items!
     */
    size_t GetProducedItems() const override { return 0; };

    /**
     * \brief returns how many items the commision worker has sold
     * \return size_t sold items
     */
    size_t GetSoldItems() const override;

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
    size_t m_baseSalary;
    size_t m_commisionPerPiece;
    size_t m_piecesSold;
};

#endif // !COMISSION_WORKER_H