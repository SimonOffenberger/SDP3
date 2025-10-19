#ifndef EMPLOYEE_H
#define EMPLOYEE_H

#include <string>
#include <chrono>
#include "Object.hpp"
#include "TWorker.hpp"

using TDateBirthday = std::chrono::year_month_day;
using TDateYear = std::chrono::year;

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
        TDateYear       dateJoined,
        TDateBirthday   TDateBirthdaydateBirth,
        std::string     socialSecurityNumber,
        TWorker         workerType
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
    virtual TDateBirthday GetDateBirth() const;

    /**
     * \brief HERE
     *
     * \param
     * \param
     */
    virtual TDateYear GetDateJoined() const;

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
    TDateYear m_dateJoined;
    TDateBirthday m_dateBirth;
    std::string m_socialSecurityNumber;
    TWorker m_workerType;
};

#endif // EMPLOYEE_H