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

    std::string GetID() const;


    /**
     * \brief HERE
     *
     * \param
     * \param
     */
    virtual TWorker GetWorkerType() const = 0;

    /**
     * \brief HERE
     *
     * \param
     * \param
     */
     // Implement inside Employee with  0 return
     // implement for non 0 classes
    virtual size_t GetProducedItems() const;

    /**
     * \brief HERE
     *
     * \param
     * \param
     */
    virtual size_t GetSoldItems() const;

    /**
     * \brief HERE
     *
     * \param
     * \param
     */
    virtual size_t GetSalary() const = 0;    
    
    /**
     * \brief HERE
     *
     * \param
     * \param
     */
    virtual TDate GetDateBirth() const = 0;

    /**
     * \brief HERE
     *
     * \param
     * \param
     */
     // TODO: look up final functionality
    std::ostream& PrintDatasheet(std::ostream& ost) const;

    /**
     * \brief HERE
     *
     * \param
     * \param
     */
    virtual std::ostream& PrintSpecificData(std::ostream& ost) const = 0;

    virtual Employee* Clone() const = 0;

protected:


    std::string m_name;
    std::string m_nameIdentifier;
    TDate m_dateJoined;
    TDate m_dateBirth;
    std::string m_socialSecurityNumber;
};

#endif // EMPLOYEE_H