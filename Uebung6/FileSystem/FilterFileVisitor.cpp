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

bool FilterFileVisitor::DoFilter(const File& file)
{
	return file.GetSize() >= m_MinSize && file.GetSize() <= m_MaxSize;
}

bool FilterFileVisitor::DoFilter(const Link& link)
{
	return false;
}
