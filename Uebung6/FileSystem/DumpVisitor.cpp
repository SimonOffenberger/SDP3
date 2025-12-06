/*****************************************************************//**
 * \file DumpVisitor.cpp
 * \brief Visitor that dumps filesystem object paths to an output stream
 *
 * \author Simon
 * \date   November 2025
 *********************************************************************/
#include "DumpVisitor.hpp"
#include "Folder.hpp"
#include "File.hpp"
#include "Link.hpp"

#include <vector>
#include <algorithm>
#include <cassert>



/** \brief Visit folder and dump its path */
void DumpVisitor::Visit(const std::shared_ptr<const Folder> folder)
{
	if (m_ost.fail()) throw std::invalid_argument(ERROR_BAD_OSTREAM);
	if (folder == nullptr) throw std::invalid_argument(ERROR_NULLPTR);

	Dump(folder);
}

/** \brief Visit file and dump its path */
void DumpVisitor::Visit(const std::shared_ptr<const File> file)
{
	if (m_ost.fail()) throw std::invalid_argument(ERROR_BAD_OSTREAM);
	if (file == nullptr) throw std::invalid_argument(ERROR_NULLPTR);

	Dump(file);
}

/** \brief Visit link and dump its path */
void DumpVisitor::Visit(const std::shared_ptr<const Link> Link)
{
	if (m_ost.fail()) throw std::invalid_argument(ERROR_BAD_OSTREAM);
	if (Link == nullptr) throw std::invalid_argument(ERROR_NULLPTR);

	Dump(Link);
}

/** \brief Dump full path for a FSObject to the internal ostream */
void DumpVisitor::Dump(const std::shared_ptr<const FSObject> fsobj)
{
	assert(m_ost.good());
	assert(fsobj != nullptr);

	// Get parent pointer
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

