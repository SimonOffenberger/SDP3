#include "FilterVisitor.hpp"
#include "Folder.hpp"
#include "File.hpp"
#include "Link.hpp"

#include <vector>
#include <algorithm>
#include <iostream>

using namespace std;

void FilterVisitor::Visit(std::shared_ptr<File>  file)
{
	if(DoFilter(file))
	{
		m_FilterCont.push_back(file);
	}
}

void FilterVisitor::Visit(std::shared_ptr<Link>  link)
{
	if (DoFilter(link))
	{
		m_FilterCont.push_back(link);
	}
}


static void Dump(FSObj_Wptr fsobj, ostream & ost) {

	std::vector<FSObject::Sptr> path_components;

	FSObj_Sptr fsobj_ptr = fsobj.lock();
	
	if (fsobj_ptr == 0) throw FilterVisitor::ERROR_NULLPTR;

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


void FilterVisitor::DumpFiltered(std::ostream& ost) const
{
	
	for_each(m_FilterCont.cbegin(), m_FilterCont.cend(), [&](FSObj_Wptr obj) {
		Dump(obj,ost);
	});
}
