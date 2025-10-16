#ifndef PIECE_WORKER_H
#define PIECE_WORKER_H

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
    std::ostream& PrintSpecificData(std::ostream& ost) const  override;

    /**
     * \brief HERE
     *
     * \param
     * \param
     */
    size_t GetProducedItems() const override;

    /**
     * \brief HERE
     *
     * \param
     * \param
     */
    TWorker GetWorkerType();

private:
    size_t m_numberPieces;
    size_t m_comissionPerPiece;
};
#endif // PIECE_WORKER_H