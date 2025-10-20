#ifndef COMPANY_HPP
#define COMPANY_HPP

#include <map>
#include <string>
#include "Object.hpp"
#include "IComp.hpp"

using  TContEmployee = std::map<const std::string,Employee const *>;

class Company : public Object, public IComp{
public:

	Company(std::string name) : m_companyName{ name } {}

	Company(const Company & comp);

	void operator=(Company comp);

	virtual void AddEmployee(Employee const* empl) override;

	virtual size_t GetCompanySize() const override;

	virtual size_t GetWorkerCount(const TWorker& workerType) const override;

	virtual size_t GetSoldItems() const override;

	virtual size_t GetProducedItems() const override;

	virtual size_t GetCountWorkerBeforDate(const TDate& date) const override;

	virtual Employee const * FindWorkerByID(const std::string& id) const override;

	virtual Employee const * GetLongestServing(void) const override;

	virtual std::ostream& PrintDataSheet(std::ostream& ost) const override;

	~Company();

private:

	std::string m_companyName;
	TContEmployee m_Employees;
};

#endif // !COMPANY_HPP
