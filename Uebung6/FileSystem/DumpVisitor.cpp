#include "DumpVisitor.hpp"

#include "Folder.hpp"
#include "File.hpp"
#include "Link.hpp"

#include <vector>
#include <algorithm>
#include <cassert>

void DumpVisitor::Visit(std::shared_ptr<Folder>  folder)
{
	if (m_ost.fail()) throw ERROR_BAD_OSTREAM;
	if (folder == nullptr) throw ERROR_NULLPTR;

	Dump(move(folder));
}

void DumpVisitor::Visit(std::shared_ptr<File>  file)
{
	if (m_ost.fail()) throw ERROR_BAD_OSTREAM;
	if (file == nullptr) throw ERROR_NULLPTR;

	Dump(move(file));
}

void DumpVisitor::Visit(std::shared_ptr<Link>  Link)
{
	if (m_ost.fail()) throw ERROR_BAD_OSTREAM;
	if (Link == nullptr) throw ERROR_NULLPTR;

	Dump(move(Link));
}

void DumpVisitor::Dump(std::shared_ptr<FSObject> fsobj)
{
	assert(fsobj != nullptr);

	std::vector<FSObject::Sptr> path_components;
	path_components.reserve(10); // reserve some space to avoid multiple allocations

	FSObject::Sptr parent = fsobj->GetParent().lock();
	FSObject::Sptr next_parent;

	while (parent != nullptr) {
		next_parent = parent->GetParent().lock();
		path_components.emplace_back(move(parent));
		parent = move(next_parent);
	}

	for_each(path_components.rbegin(), path_components.rend(),
		[&](const FSObject::Sptr & obj) {
			m_ost << obj->GetName() << "\\";
		});

	m_ost << fsobj->GetName() << "\n";

}

