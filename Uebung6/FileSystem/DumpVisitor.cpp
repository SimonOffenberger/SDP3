#include "DumpVisitor.hpp"

#include "Folder.hpp"
#include "File.hpp"
#include "Link.hpp"

#include <vector>
#include <algorithm>

void DumpVisitor::Visit(const Folder& folder)
{
	if (m_ost.fail()) throw ERROR_BAD_OSTREAM;
	Dump(folder);
}

void DumpVisitor::Visit(const File& file)
{
	if (m_ost.fail()) throw ERROR_BAD_OSTREAM;
	Dump(file);
}

void DumpVisitor::Visit(const Link& Link)
{
	if (m_ost.fail()) throw ERROR_BAD_OSTREAM;
	Dump(Link);
}

void DumpVisitor::Dump(const FSObject& fsobj)
{
	std::vector<FSObject::Sptr> path_components;

	FSObject::Sptr parent = fsobj.GetParent().lock();

	while (parent != nullptr) {

		path_components.push_back(parent);
		parent = parent->GetParent().lock();
	}

	for_each(path_components.rbegin(), path_components.rend(),
		[&](const FSObject::Sptr& obj) {
			m_ost << obj->GetName() << "\\";
		});

	m_ost << fsobj.GetName() << "\n";

}

