/*****************************************************************//**
 * \file   IComp.hpp
 * \brief  Interface which is implemented by the company and used by the client
 * 
 * \author Simon Offenberger
 * \date   October 2025
 *********************************************************************/
#ifndef ICOMP_HPP
#define ICOMP_HPP

#include <string>
#include "TWorker.hpp"
#include "Employee.hpp"

class IComp{
public:

	/**
	 * \brief Gets the current size of the company.
	 *
	 * \return Size of the company
	 */
	virtual size_t GetCompanySize() const = 0;

	/**
	 * \brief Get the Count of a specific Worker Type.
	 *
	 * \param workerType Worker Type from which the count should be determined
	 * \return Count of the Worker Type in the Company
	 */
	virtual size_t GetWorkerCount(const TWorker & workerType) const = 0;

	/**
	 * \brief Get the amount of Sold Items in the whole company.
	 *
	 * \return Amout of Sold Items
	 */
	virtual size_t GetSoldItems() const = 0;

	/**
	 * \brief Get the amount of produced items.
	 *
	 * \return Amout of produced Items
	 */
	virtual size_t GetProducedItems() const = 0;

	/**
	 * \brief Get the of worker with birth date bevor date.
	 *
	 * \param date to get the employees which are older
	 * \return Amout of employees which are older than the passed in birthdate
	 */
	virtual size_t GetCountWorkerBeforDate(const TDate & date) const = 0;

	/**
	 * \brief Find a worker with a specific ID.
	 *
	 * \param id ID for which should be searched for
	 * \return nullptr if no Empl is found
	 * \return Pointer to Employee
	 */
	virtual Employee const * FindWorkerByID(const std::string & id) const = 0;
	
	/**
	 * \brief Get the Employee which has been the longest serving.
	 *
	 * \return nullptr if company is empty
	 * \return Pointer to Employee
	 */
	virtual Employee const * GetLongestServing(void) const = 0;

	/**
	 * \brief Prints a Datasheet for each employee.
	 *
	 * \param ost ostream where the Datasheet should be printed at
	 * \return referenced ostream
	 */
	virtual std::ostream& PrintDataSheet(std::ostream& ost) const = 0;

	/**
	 * \brief Adds am Employee to the Company
	 * \brief The company now owns the Employee and is responsible for destructing of Employee.
	 *
	 * \param empl Employee that should be added to the Company
	 * \throw ERROR_DUPLICATE_EMPL if ID of Employee is already in the collection
	 * \throw ERROR_NULLPTR if an Nullptr is passed in
	 */
	virtual void AddEmployee(Employee const* empl) = 0;

	/**
	 * \brief Virtual Dtor of Icomp.
	 * 
	 */
	virtual ~IComp() = default;
};

#endif // !ICOMP_HPP