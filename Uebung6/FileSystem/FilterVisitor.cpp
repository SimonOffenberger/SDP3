#include "FilterVisitor.hpp"
#include "Folder.hpp"
#include "File.hpp"
#include "Link.hpp"

#include <vector>
#include <algorithm>
#include <iostream>

using namespace std;

void FilterVisitor::Visit(const File& file)
{
	if(DoFilter(file))
	{
		m_FilterCont.push_back(&file);
	}
}

void FilterVisitor::Visit(const Link& link)
{
	if (DoFilter(link))
	{
		m_FilterCont.push_back(&link);
	}
}


static void Dump(const FSObject * const fsobj, ostream & ost) {

	std::vector<FSObject::Sptr> path_components;

	FSObject::Sptr parent = fsobj->GetParent().lock();

	while (parent != nullptr) {

		path_components.push_back(parent);
		parent = parent->GetParent().lock();
	}

	for_each(path_components.rbegin(), path_components.rend(),
		[&](const FSObject::Sptr& obj) {
			ost << obj->GetName() << "\\";
		});

	ost << fsobj->GetName();

	std::shared_ptr<const ILink> link_ptr = fsobj->AsLink();

	if (link_ptr) {
		ost << " -> " << (**link_ptr)->GetName();
	}

	ost << "\n";
}


void FilterVisitor::DumpFiltered(std::ostream& ost) const
{
	
	for_each(m_FilterCont.cbegin(), m_FilterCont.cend(), [&](const FSObject * obj) {
		Dump(obj,ost);
	});
}
