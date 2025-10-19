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

    /**
     * \brief HERE
     *
     * \param
     * \param
     */
     // Implement inside Employee with  0 return
     // implement for non 0 classes
    virtual size_t GetProducedItems() const = 0;

    /**
     * \brief HERE
     *
     * \param
     * \param
     */
    virtual size_t GetSoldItems() const = 0;

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
    virtual TDate GetDateBirth() const;

    /**
     * \brief HERE
     *
     * \param
     * \param
     */
    virtual TDate GetDateJoined() const;

    /**
     * \brief HERE
     *
     * \param
     * \param
     */
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