#ifndef BOSS_H
#define BOSS_H

#include "Employee.hpp"

class Boss : public Employee
{
public:
    /**
     * \brief HERE
     *
     * \param
     * \param
     */
    std::ostream& PrintSpecificData(std::ostream& ost) override;

    /**
     * \brief HERE
     *
     * \param
     * \param
     */
    size_t GetSalary() override;
    
    /**
     * \brief HERE
     *
     * \param
     * \param
     */
    TWorker GetWorkerType();

private:
    size_t m_salary;
};

#endif // BOSS_H