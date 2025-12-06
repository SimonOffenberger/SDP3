/*****************************************************************//**
 * \file FilterFileVisitor.cpp
 * \brief Visitor that filters files by size range
 *
 * \author Simon
 * \date   November 2025
 *********************************************************************/
#include "FilterFileVisitor.hpp"
#include "Folder.hpp"
#include "File.hpp"
#include "Link.hpp"

/** \brief Construct filter with size bounds */
FilterFileVisitor::FilterFileVisitor(const size_t min, const size_t max)
{
	if (min >= max) throw std::invalid_argument(ERROR_INVALID_SIZE_RANGE);

	m_MinSize = min;
	m_MaxSize = max;
}

/** \brief Accept files whose size is within range */
bool FilterFileVisitor::DoFilter(const std::shared_ptr<const File>& file) const
{
	if (file == nullptr) throw std::invalid_argument(ERROR_NULLPTR);

	return file->GetSize() >= m_MinSize && file->GetSize() <= m_MaxSize;
}

/** \brief Links are not accepted by file filter */
bool FilterFileVisitor::DoFilter(const std::shared_ptr<const Link>& link) const
{
	if (link == nullptr) throw std::invalid_argument(ERROR_NULLPTR);

	return false;
}
