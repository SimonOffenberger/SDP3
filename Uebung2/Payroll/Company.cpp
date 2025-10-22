/*****************************************************************//**
 * \file   Company.hpp
 * \brief  Company that holds Employees and provides information about the
 * \brief  Employees of the company.
 *
 * \author Simon Offenberger
 * \date   October 2025
 *********************************************************************/
#include <algorithm>
#include <numeric>
#include <iostream>
#include "Company.hpp"
#include "Employee.hpp"
using namespace std;

/**
 * \brief Ostream manipulater for creating a horizontal line.
 *
 * \return string
 */
static ostream & hline(ostream & ost) {

	ost << string(60, '-') << endl;
	return ost;
}

/**
 * \brief Ostream manipulater for creating a horizontal line.
 *
 * \return string
 */
static ostream & hstar(ostream & ost) {

	ost << string(60, '*') << endl;
	return ost;
}

void Company::AddEmployee(Employee const* empl)
{
	if (empl == nullptr) throw Object::ERROR_NULLPTR;
	// insert returns a pair. First = Iterator, Second bool -> bool indicates if the insertion was succsessful.
	if (!m_Employees.insert({ empl->GetID(),empl }).second) throw Company::ERROR_DUPLICATE_EMPL;
}

Company::Company(const Company& comp)
{
	// copy Company name
	m_companyName = comp.m_companyName;

	// clone all employees from one company to the other
	for_each(
		comp.m_Employees.cbegin(), comp.m_Employees.cend(),
		[&](auto& e) {AddEmployee(e.second->Clone());
		});
}

void Company::operator=(Company comp)
{
	std::swap(m_Employees, comp.m_Employees);
	std::swap(m_companyName, comp.m_companyName);
}

size_t Company::GetCompanySize() const
{
	return m_Employees.size();
}

size_t Company::GetWorkerCount(const TWorker& workerType) const
{
	// Count all Employees where workerType is equal
	return count_if(m_Employees.cbegin(), m_Employees.cend(),
					[&](auto& e) {return e.second->GetWorkerType() == workerType;});
}

size_t Company::GetSoldItems() const
{
	return accumulate(m_Employees.cbegin(), m_Employees.cend(),static_cast<size_t>(0),
		[](size_t val, const auto& e) { return val + e.second->GetSoldItems();});
}

size_t Company::GetProducedItems() const
{
	return accumulate(m_Employees.cbegin(), m_Employees.cend(), static_cast<size_t>(0),
		[](size_t val, const auto& e) { return val + e.second->GetProducedItems();});
}

size_t Company::GetCountWorkerBeforDate(const TDate& date) const
{
	return count_if(m_Employees.cbegin(), m_Employees.cend(),
		[&](const auto& e) {return e.second->GetDateBirth() < date;});
}

Employee const * Company::FindWorkerByID(const std::string& id) const
{
	auto empl = m_Employees.find(id);

	if (empl == m_Employees.end()) return nullptr;
	else return empl->second;
}

Employee const * Company::GetLongestServing(void) const
{
	auto minElem = min_element(m_Employees.cbegin(), m_Employees.cend(),
		[](const auto& lhs, const auto& rhs) { return lhs.second->GetDateJoined() < rhs.second->GetDateJoined();});

	if (minElem == m_Employees.end()) return nullptr;
	else return minElem->second;

}

std::ostream& Company::PrintDataSheet(std::ostream& ost) const
{

	// convert system clock.now to days -> this can be used in CTOR for year month day
	std::chrono::year_month_day date{ floor<std::chrono::days>(std::chrono::system_clock::now()) };

	if (!ost.good()) throw Object::ERROR_BAD_OSTREAM;

	ost << hstar;
	ost << m_companyName << endl;
	ost << hstar;
	
	for_each(m_Employees.cbegin(), m_Employees.cend(), [&](const auto& e) { e.second->PrintDatasheet(ost);});

	ost << hline;
	ost << date.month() << " " << date.year() << endl;
	ost << hline;

	if (ost.fail()) throw Object::ERROR_FAIL_WRITE;

	return ost;
}

Company::~Company()
{
	for (auto & elem : m_Employees)
	{
		delete elem.second;
	}

	m_Employees.clear();
}
