/*****************************************************************//**
 * \file   RecordEntry.hpp
 * \brief  Class that defines an entry in a dirve record.
 * \brief  This record entry is used by the drive record class.
 * \brief  The drive record class stores multiple record entries.
 * 
 * \author Simon Offenberger
 * \date   October 2025
 *********************************************************************/
#ifndef RECORD_ENTRY_HPP
#define RECORD_ENTRY_HPP


#include <chrono>
#include "Object.hpp"

// Using Statement for date type
using TDate = std::chrono::year_month_day;

class RecordEntry : public Object {
public:

	/**
	 * \brief CTOR of a drive record.
	 * 
	 * \param date : date when the drive happend
	 * \param distance : the distance of the drive in km
	 */
	RecordEntry(const TDate & date,const size_t & distance) : m_date{ date }, m_distance{ distance } {}

	/**
	 * \brief Getter of the distance member of the Record Entry Class.
	 * 
	 * \return Distance of this Record Entry
	 */
	size_t GetDistance() const;

	/**
	 * \brief Getter of the data member of the Record Entry Class.
	 * 
	 * \return Date of this Record Entry
	 */
	TDate GetDate() const;

	/**
	 * \brief Formatted output of this Record Entry on an ostream.
	 * 
	 * \param ost : Refernce to an ostream where the Entry should be printed at.
	 * \return Referenced ostream
	 */
	virtual std::ostream& Print(std::ostream& ost = std::cout) const override;

	/**
	 * \brief less than operater, is used for storing the Entries in a multiset.
	 * 
	 * \param rh : Righthandside of the less than operator
	 * \return true:  left hand side is less than the right hand side.
	 * \return false: left hand side is greather or equal than the right hand side.
	 */
	bool operator<(const RecordEntry& rh) const;

private:
	TDate m_date;		// private date member
	size_t m_distance;	// private distance member
};


#endif // !1