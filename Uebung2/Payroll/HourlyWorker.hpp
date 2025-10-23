/*****************************************************************//**
 * \file   HourlyWorker.hpp
 * \brief  HourlyWorker Class - Inherits from Employee
 * \author Simon
 * \date   October 2025
 *********************************************************************/
#ifndef HOURLY_WORKER_HPP
#define HOURLY_WORKER_HPP

#include "Employee.hpp"

class HourlyWorker : public Employee
{
public:

    
    HourlyWorker(
        const std::string & name,
        const std::string & nameID,
        const TDate & dateJoined,
        const TDate & dateBirth,
        const std::string & socialSecurityNumber,
        const size_t & hourlyRate,
        const size_t & workedHours
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

    size_t m_hourlyRate;
    size_t m_workedHours;
};

#endif // !HOURLY_WORKER_HPP