#include "FilterLinkVisitor.hpp"
#include <cassert>

/** \brief Files are not accepted by link filter */
bool FilterLinkVisitor::DoFilter(const std::shared_ptr<File>& file)
{
	assert(file != nullptr);
	return false;
}

/** \brief Links are accepted by link filter */
bool FilterLinkVisitor::DoFilter(const std::shared_ptr<Link>& link)
{
	assert(link != nullptr);
	return true;
}
