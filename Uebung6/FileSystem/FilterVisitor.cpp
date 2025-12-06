/*****************************************************************//**
 * \file FilterVisitor.cpp
 * \brief Visitor that filters filesystem objects based on criteria defines in derived classes
 *
 * \author Simon
 * \date   November 2025
 *********************************************************************/
#include "FilterVisitor.hpp"
#include "Folder.hpp"
#include "File.hpp"
#include "Link.hpp"

#include <vector>
#include <iostream>
#include <cassert>
#include <stdexcept>


void FilterVisitor::DumpPath(const std::weak_ptr<const FSObject> & fsobj, std::ostream& ost) const
{
	// end recursion on expired weak pointer
	if (fsobj.expired()) return;

	const auto obj = fsobj.lock();
	if (!obj) return; // defensive: lock could fail

	// first dump parent path
	DumpPath(obj->GetParent(), ost);

	if (!ost.good()) throw std::invalid_argument(FilterVisitor::ERROR_BAD_OSTREAM);

	ost << "\\" << obj->GetName();

	const std::shared_ptr<const ILink> link_ptr = obj->AsLink();

	if (link_ptr) {
		const FSObject::Sptr linked_obj = link_ptr->GetReferncedFSObject();
		if (linked_obj) {
			ost << " -> " << linked_obj->GetName();
		}
		else {
			ost << " -> " << "linked Object Expired!";
		}
	}
}

/** \brief Default visit for folder (no-op) */
void FilterVisitor::Visit(const std::shared_ptr<const Folder> folder)
{
	if (folder == nullptr) throw std::invalid_argument(ERROR_NULLPTR);
}

/** \brief Visit a file and if it matches add to filtered container */
void FilterVisitor::Visit(const std::shared_ptr<const File> file)
{
	if (file == nullptr) throw std::invalid_argument(ERROR_NULLPTR);

	// if file matches filter add to container
	if(DoFilter(file))
	{
		m_FilterCont.emplace_back(file);
	}
}

/** \brief Visit a link and if it matches add to filtered container */
void FilterVisitor::Visit(const std::shared_ptr<const Link> link)
{
	if (link == nullptr) throw std::invalid_argument(ERROR_NULLPTR);

	// if link matches filter add to container
	if (DoFilter(link))
	{
		m_FilterCont.emplace_back(link);
	}
}

/** \brief Dump all filtered objects to given ostream */
void FilterVisitor::DumpFiltered(std::ostream& ost) const
{
	if (!ost.good()) throw std::invalid_argument(FilterVisitor::ERROR_BAD_OSTREAM);

	for (const auto & obj : m_FilterCont) {
		DumpPath(obj, ost);
		ost << '\n';
	}
}

/** \brief Return the filtered objects container */
const FilterVisitor::TContFSobj& FilterVisitor::GetFilteredObjects() const
{
	return m_FilterCont;
}

