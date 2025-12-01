#include "FilterFileVisitor.hpp"

#include "Folder.hpp"
#include "File.hpp"
#include "Link.hpp"

/** \brief Construct filter with size bounds */
FilterFileVisitor::FilterFileVisitor(const size_t min, const size_t max)
{
	if (min >= max) throw ERROR_INVALID_SIZE_RANGE;

	m_MinSize = min;
	m_MaxSize = max;
}

/** \brief Accept files whose size is within range */
bool FilterFileVisitor::DoFilter(const std::shared_ptr<File>& file)
{
	if (file == nullptr) throw ERROR_NULLPTR;

	return file->GetSize() >= m_MinSize && file->GetSize() <= m_MaxSize;
}

/** \brief Links are not accepted by file filter */
bool FilterFileVisitor::DoFilter(const std::shared_ptr<Link>& link)
{
	if (link == nullptr) throw ERROR_NULLPTR;

	return false;
}
