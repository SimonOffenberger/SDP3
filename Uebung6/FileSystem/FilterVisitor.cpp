#include "FilterVisitor.hpp"
#include "Folder.hpp"
#include "File.hpp"
#include "Link.hpp"

#include <vector>
#include <algorithm>
#include <iostream>
#include <cassert>

using namespace std;

void FilterVisitor::DumpPath(const FSObj_Wptr & fsobj, std::ostream& ost) const
{
	if (fsobj.expired()) return;

	FSObject::Sptr obj = fsobj.lock();

	DumpPath(obj->GetParent(), ost);

	if (obj) {
		ost << "\\" << obj->GetName();

		std::shared_ptr<const ILink> link_ptr = obj->AsLink();

		if (link_ptr) {
			const FSObject::Sptr linked_obj = link_ptr->GetReferncedFSObject();
			if (linked_obj) {
				ost << " -> " << link_ptr->GetReferncedFSObject()->GetName();
			}
			else {
				ost << " -> " << "linked Object Expired!";
			}
		}
	}
}

/** \brief Default visit for folder (no-op) */
void FilterVisitor::Visit(const std::shared_ptr<Folder>& folder)
{	
	if (folder == nullptr) throw ERROR_NULLPTR;
}

/** \brief Visit a file and if it matches add to filtered container */
void FilterVisitor::Visit(const std::shared_ptr<File>& file)
{	
	if (file == nullptr) throw ERROR_NULLPTR;

	// if file matches filter add to container
	if(DoFilter(file))
	{
		m_FilterCont.emplace_back(file);
	}
}

/** \brief Visit a link and if it matches add to filtered container */
void FilterVisitor::Visit(const std::shared_ptr<Link>& link)
{
	if (link == nullptr) throw ERROR_NULLPTR;


	// if link matches filter add to container
	if (DoFilter(link))
	{
		m_FilterCont.emplace_back(link);
	}
}

/** \brief Dump all filtered objects to given ostream */
void FilterVisitor::DumpFiltered(std::ostream& ost) const
{
	if (ost.fail()) throw FilterVisitor::ERROR_BAD_OSTREAM;

	for_each(m_FilterCont.cbegin(), m_FilterCont.cend(), [&](const auto & obj) {
		DumpPath(obj, ost);
		ost << "\n";
	});
}

/** \brief Return the filtered objects container */
const FilterVisitor::TContFSobj& FilterVisitor::GetFilteredObjects() const
{
	return m_FilterCont;
}

