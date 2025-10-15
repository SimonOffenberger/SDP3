/*****************************************************************//**
 * \file   DriveRecord.hpp
 * \brief  This Class implements a drive record book which holds multiple
 * \brief  record entries in a TCont, which is defined as a multiset.
 * \brief  The multiset is used because it stores the data sorted.
 * \brief  This sorting mandatory because the entries should be date ascending.
 * 
 * \author Simon Offenberger
 * \date   October 2025
 *********************************************************************/
#ifndef DRIVE_RECORD_HPP
#define DRIVE_RECORD_HPP

#include <set>
#include "RecordEntry.hpp"
#include "Object.hpp"

// Using statement for the used container to store the record entries
using TCont = std::multiset<RecordEntry>;

class DriveRecord : public Object {
public:

	/**
	 * \brief Methode for adding a record entry to a collection of drive records.
	 * 
	 * \param entry : Record to be added to the colletion
	 */
	void AddRecord(const RecordEntry & entry);

	/**
	 * \brief This methode adds up all the distance of all record entries.
	 * 
	 * \return the sum of all distances in the collection
	 */
	size_t GetMilage() const;

	/**
	 * \brief Formatted output of all Record Entry on an ostream.
	 *
	 * \param ost : Refernce to an ostream where the Entries should be printed at.
	 * \return Referenced ostream
	 */
	virtual std::ostream& Print(std::ostream& ost = std::cout) const;

private:

	TCont m_driveRecords;
};


#endif // !1