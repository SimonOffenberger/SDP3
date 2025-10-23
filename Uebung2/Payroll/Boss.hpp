/*****************************************************************//**
 * \file   Boss.hpp
 * \brief  Boss Class - inherits from Employee
 * \author Simon Vogelhuber
 * \date   October 2025
 *********************************************************************/
#ifndef BOSS_H
#define BOSS_H

#include "Employee.hpp"

class Boss : public Employee
{
public:

    Boss(
        const std::string & name,
        const std::string & nameID,
        const TDate & dateJoined,
        const TDate & dateBirth,
        const std::string & socialSecurityNumber,
        const size_t & salary
    );


    /**
     * \brief Just here because of whacky class structure.
     * Worker does not strictly produce items!
     */
    size_t GetProducedItems() const override { return 0; };

    /**
     * \brief Just here because of whacky class structure.
     * Worker Does not sell items!
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

private:
    /**
     * \brief Prints worker specific information
     * \param std::ostream& ost
     * \return std::ostream&
     */
    std::ostream& DoPrintSpecificData(std::ostream& ost) const override;

    size_t m_salary;
};

#endif // BOSS_H