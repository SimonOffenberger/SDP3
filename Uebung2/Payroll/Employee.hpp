#ifndef EMPLOYEE_H
#define EMPLOYEE_H

#include <string>
#include <chrono>
#include "Object.hpp"

using TDate = std::chrono::year_month_day;

enum TWorker
{
    Boss,
    CommisionWorker,
    HourlyWorker,
    PieceWorker
};

class Employee: public Object
{
public:
    /**
     * \brief HERE
     *
     * \param 
     * \param
     */
    virtual TWorker GetWorkerType() = 0;

    /**
     * \brief HERE
     *
     * \param
     * \param
     */
    // Implement inside Employee with  0 return
    // implement for non 0 classes
    virtual size_t GetProducedItems();

    /**
     * \brief HERE
     *
     * \param
     * \param
     */
    virtual size_t GetSoldItems();

    /**
     * \brief HERE
     *
     * \param
     * \param
     */
    virtual size_t GetSalary() = 0;

    /**
     * \brief HERE
     *
     * \param
     * \param
     */
    // TODO: look up final functionality
    virtual std::ostream& PrintDatasheet(std::ostream& ost) final;
    
    /**
     * \brief HERE
     *
     * \param
     * \param
     */
    virtual std::ostream& PrintSpecificData(std::ostream& ost) = 0;

private:
protected:
    std::string m_name;
    std::string m_nameIdentifier;
    TDate m_dateJoined;
    TDate m_dateBirth;
    std::string m_socialSecurityNumber;
}

#endif // EMPLOYEE_H