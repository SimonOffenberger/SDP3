#include "FilterFileVisitor.hpp"

#include "Folder.hpp"
#include "File.hpp"
#include "Link.hpp"

FilterFileVisitor::FilterFileVisitor(const size_t& min, const size_t& max)
{
	if (min >= max) throw ERROR_INVALID_SIZE_RANGE;

	m_MinSize = min;
	m_MaxSize = max;
}

bool FilterFileVisitor::DoFilter(std::shared_ptr<File> file)
{
	if (file == nullptr) throw ERROR_NULLPTR;

	return file->GetSize() >= m_MinSize && file->GetSize() <= m_MaxSize;
}

bool FilterFileVisitor::DoFilter(std::shared_ptr<Link> link)
{
	if (link == nullptr) throw ERROR_NULLPTR;

	return false;
}
