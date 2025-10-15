#ifndef ICOMP_HPP
#define ICOMP_HPP

#include <string>
#include "TWorker.hpp"
#include "Employee.hpp"

class IComp{
public:

	virtual size_t GetCompanySize() = 0;

	virtual size_t GetWorkerCount(TWorker workerType) = 0;

	virtual size_t GetSoldItems() = 0;

	virtual size_t GetProducedItems() = 0;

	virtual size_t GetCountWorkerBeforData(TDate date) = 0;

	virtual Employee* FindWorkerByID(std::string) = 0;
	
	virtual Employee* GetLongestServing(void) = 0;

	virtual std::ostream& PrintDataSheet(std::ostream& ost) = 0;

	
};

#endif // !ICOMP_HPP