#include "DumpVisitor.hpp"

#include "Folder.hpp"
#include "File.hpp"
#include "Link.hpp"

#include <vector>
#include <algorithm>
#include <cassert>



/** \brief Visit folder and dump its path */
void DumpVisitor::Visit(const std::shared_ptr<Folder>& folder)
{
	if (m_ost.fail()) throw ERROR_BAD_OSTREAM;
	if (folder == nullptr) throw ERROR_NULLPTR;

	Dump(folder);
}

/** \brief Visit file and dump its path */
void DumpVisitor::Visit(const std::shared_ptr<File>& file)
{
	if (m_ost.fail()) throw ERROR_BAD_OSTREAM;
	if (file == nullptr) throw ERROR_NULLPTR;

	Dump(file);
}

/** \brief Visit link and dump its path */
void DumpVisitor::Visit(const std::shared_ptr<Link>& Link)
{
	if (m_ost.fail()) throw ERROR_BAD_OSTREAM;
	if (Link == nullptr) throw ERROR_NULLPTR;

	Dump(Link);
}

/** \brief Dump full path for a FSObject to the internal ostream */
void DumpVisitor::Dump(const std::shared_ptr<FSObject>& fsobj)
{
	assert(fsobj != nullptr);

	FSObject::Sptr parent = fsobj->GetParent().lock();

	// Print an indentation token for each ancestor
	while (parent != nullptr) {
		m_ost << "|  ";
		parent = parent->GetParent().lock();
	}

	m_ost << "|---[" << fsobj->GetName();

	if (fsobj->AsFolder()) {
		m_ost << "/]\n";
	}
	else if (fsobj->AsLink()) {
		m_ost << "->]\n";
	}
	else {
		m_ost << "]\n";
	}
}

