#include "Employee.hpp"

class PieceWorker : public Employee
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
    size_t GetProducedItems() override;

    /**
     * \brief HERE
     *
     * \param
     * \param
     */
    TWorker GetWorkerType();

private:
    size_t n_hourlyRate;
    size_t m_workedHours;
};