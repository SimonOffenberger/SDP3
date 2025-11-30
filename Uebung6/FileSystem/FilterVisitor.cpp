#include "FilterVisitor.hpp"
#include "Folder.hpp"
#include "File.hpp"
#include "Link.hpp"

#include <vector>
#include <algorithm>
#include <iostream>
#include <cassert>

using namespace std;

/** \brief Default visit for folder (no-op) */
void FilterVisitor::Visit(const std::shared_ptr<Folder>& folder)
{	
	if (folder == nullptr) throw ERROR_NULLPTR;
}

/** \brief Visit a file and if it matches add to filtered container */
void FilterVisitor::Visit(const std::shared_ptr<File>& file)
{	
	if (file == nullptr) throw ERROR_NULLPTR;

	if(DoFilter(file))
	{
		m_FilterCont.emplace_back(file);
	}
}

/** \brief Visit a link and if it matches add to filtered container */
void FilterVisitor::Visit(const std::shared_ptr<Link>& link)
{
	if (link == nullptr) throw ERROR_NULLPTR;

	if (DoFilter(link))
	{
		m_FilterCont.emplace_back(link);
	}
}


static void Dump(FSObj_Wptr fsobj, ostream & ost) {

	std::vector<FSObject::Sptr> path_components;

	FSObj_Sptr fsobj_ptr = fsobj.lock();
	
	if (fsobj_ptr ==0) throw FilterVisitor::ERROR_NULLPTR;

	FSObject::Sptr parent = fsobj_ptr->GetParent().lock();

	while (parent != nullptr) {

		path_components.push_back(parent);
		parent = parent->GetParent().lock();
	}

	for_each(path_components.rbegin(), path_components.rend(),
		[&](const FSObject::Sptr & obj) {
			ost << obj->GetName() << "\\";
		});

	ost << fsobj_ptr->GetName();

	std::shared_ptr<const ILink> link_ptr = fsobj_ptr->AsLink();

	if (link_ptr) { 
		FSObject::Sptr linked_obj = link_ptr->GetReferncedFSObject();
		if (linked_obj) {
			ost << " -> " << link_ptr->GetReferncedFSObject()->GetName();
		}
	}

	ost << "\n";
}


/** \brief Dump all filtered objects to given ostream */
void FilterVisitor::DumpFiltered(std::ostream& ost) const
{
	if (ost.fail()) throw FilterVisitor::ERROR_BAD_OSTREAM;

	for_each(m_FilterCont.cbegin(), m_FilterCont.cend(), [&](const auto & obj) {
		Dump(obj,ost);
	});
}

/** \brief Return the filtered objects container */
const FilterVisitor::TContFSobj& FilterVisitor::GetFilteredObjects() const
{
	return m_FilterCont;
}
