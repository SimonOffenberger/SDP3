/*****************************************************************//**
 * \file   Company.hpp
 * \brief  Company that holds Employees and provides information about the 
 * \brief  Employees of the company.
 * 
 * \author Simon Offenberger
 * \date   October 2025
 *********************************************************************/
#ifndef COMPANY_HPP
#define COMPANY_HPP

#include <map>
#include <string>
#include "Object.hpp"
#include "IComp.hpp"

/**
 * Declaration of an alias for the used Container.
 */
using  TContEmployee = std::map<const std::string,Employee const *>;

class Company : public Object, public IComp{
public:
	/**
	 * Constant for the Excetion of an Duplicate Employee.
	 */
	inline static const std::string ERROR_DUPLICATE_EMPL = "ERROR: Duplicate Employee!";

	/**
	 * \brief CTOR for a Company.
	 * 
	 * \param name Name of the Company
	 */
	Company(const std::string & name) : m_companyName{ name } {}

	/**
	 * \brief Copy Ctor of the Company.
	 * 
	 * \param comp Refernce to the company that should be copied
	 */
	Company(const Company & comp);

	/**
	 * \brief Assignoperator for a company uses Copy and Swap.
	 * 
	 * \param comp Copy of the company
	 */
	void operator=(Company comp);

	/**
	 * \brief Adds am Employee to the Company
	 * \brief The company now owns the Employee and is responsible for destructing of Employee.
	 * 
	 * \param empl Employee that should be added to the Company
	 * \throw ERROR_DUPLICATE_EMPL if ID of Employee is already in the collection
	 * \throw ERROR_NULLPTR if an Nullptr is passed in
	 */
	virtual void AddEmployee(Employee const* empl) override;

	/**
	 * \brief Gets the current size of the company.
	 * 
	 * \return Size of the company
	 */
	virtual size_t GetCompanySize() const override;

	/**
	 * \brief Get the Count of a specific Worker Type.
	 * 
	 * \param workerType Worker Type from which the count should be determined
	 * \return Count of the Worker Type in the Company
	 */
	virtual size_t GetWorkerCount(const TWorker& workerType) const override;

	/**
	 * \brief Get the amount of Sold Items in the whole company.
	 * 
	 * \return Amout of Sold Items
	 */
	virtual size_t GetSoldItems() const override;

	/**
	 * \brief Get the amount of produced items.
	 * 
	 * \return Amout of produced Items
	 */
	virtual size_t GetProducedItems() const override;

	/**
	 * \brief Get the of worker with birth date bevor date.
	 * 
	 * \param date to get the employees which are older
	 * \return Amout of employees which are older than the passed in birthdate
	 */
	virtual size_t GetCountWorkerBeforDate(const TDate& date) const override;

	/**
	 * \brief Find a worker with a specific ID.
	 * 
	 * \param id ID for which should be searched for
	 * \return nullptr if no Empl is found 
	 * \return Pointer to Employee
	 */
	virtual Employee const * FindWorkerByID(const std::string& id) const override;

	/**
	 * \brief Get the Employee which has been the longest serving.
	 * 
	 * \return nullptr if company is empty
	 * \return Pointer to Employee
	 */
	virtual Employee const * GetLongestServing(void) const override;

	/**
	 * \brief Prints a Datasheet for each employee.
	 * 
	 * \param ost ostream where the Datasheet should be printed at
	 * \return referenced ostream
	 */
	virtual std::ostream& PrintDataSheet(std::ostream& ost) const override;

	/**
	 * \brief DTOR of the Company.
	 * 
	 */
	~Company();

private:

	std::string m_companyName;
	TContEmployee m_Employees;
};

#endif // !COMPANY_HPP
