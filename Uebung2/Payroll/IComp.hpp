#ifndef ICOMP_HPP
#define ICOMP_HPP

#include <string>
#include "TWorker.hpp"
#include "Employee.hpp"

class IComp{
public:

	virtual size_t GetCompanySize() const = 0;

	virtual size_t GetWorkerCount(const TWorker & workerType) const = 0;

	virtual size_t GetSoldItems() const = 0;

	virtual size_t GetProducedItems() const = 0;

	virtual size_t GetCountWorkerBeforDate(const TDate & date) const = 0;

	virtual Employee const * FindWorkerByID(const std::string & id) const = 0;
	
	virtual Employee const * GetLongestServing(void) const = 0;

	virtual std::ostream& PrintDataSheet(std::ostream& ost) const = 0;

	virtual void AddEmployee(Employee const* empl) = 0;

	virtual ~IComp() = default;
	
};

#endif // !ICOMP_HPP