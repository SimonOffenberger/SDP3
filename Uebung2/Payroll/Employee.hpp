/*****************************************************************//**
 * \file   Employee.cpp
 * \brief  Abstract Class for constructing Employees of all types
 * \author Simon Vogelhuber
 * \date   October 2025
 *********************************************************************/
#ifndef EMPLOYEE_H
#define EMPLOYEE_H

#include <string>
#include <chrono>
#include "Object.hpp"
#include "TWorker.hpp"

using TDate = std::chrono::year_month_day;

class Employee : public Object
{
public:

    inline static const std::string ERROR_BAD_ID = "ERROR: An employees ID is limited to 3 characters.";
    inline static const std::string ERROR_BAD_SOZIAL_SEC_NUM = "ERROR: Invalid Sozial Security Number";

    std::string GetID() const;
    
    /**
     * \brief Constructor needs every
     * member set to be called.
     * \return TWorker enum
     */
    Employee(
        std::string     name,
        std::string     nameID,
        TDate           dateJoined,
        TDate           TDateBirthdaydateBirth,
        std::string     socialSecurityNumber
    );

    /**
     * \brief Gives Information about what kind
     * of Worker it is.
     * \return TWorker enum
     */
    virtual TWorker GetWorkerType() const = 0;

    /** Pure Virtual Function
     * \brief return produced items.
     * \return size_t
     */
    virtual size_t GetProducedItems() const = 0;

    /** Pure Virtual Function
     * \brief returns sold items
     * \return size_t
     */
    virtual size_t GetSoldItems() const = 0;

    /** Pure Virtual Function
     * \brief returns total pay a worker
     * recieves.
     * \return size_t
     */
    virtual size_t GetSalary() const = 0;    
    
    /** Pure Virtual Function
     * \brief returns date of birth of a given worker.
     * \return TDate
     */
    virtual TDate GetDateBirth() const;

    /** Pure Virtual Function
     * \brief returns the date a worker.
     * has started working at the company.
     * \return TDate
     */
    virtual TDate GetDateJoined() const;

    /**
     * \brief Prints information about a worker.
     * \return std::ostream&
     */
    std::ostream& PrintDatasheet(std::ostream& ost) const;

    

    /** Pure virtual function
    * \brief creates a copy of the worker and puts it on the heap.
    * \return Employee*
    */
    virtual Employee* Clone() const = 0;


protected:

    /** Pure virtual function
    * \brief Prints specific information for a type of worker.
    * \return std::ostream&
    */
    virtual std::ostream& PrintSpecificData(std::ostream& ost) const = 0;

    std::string m_name;
    std::string m_nameIdentifier;
    TDate m_dateJoined;
    TDate m_dateBirth;
    std::string m_socialSecurityNumber;

private:
    const size_t SozialSecNumLen = 4;
};

#endif // EMPLOYEE_H