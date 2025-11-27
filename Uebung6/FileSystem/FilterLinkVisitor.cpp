#include "FilterLinkVisitor.hpp"

bool FilterLinkVisitor::DoFilter(std::shared_ptr<File> file)
{
	return false;
}

bool FilterLinkVisitor::DoFilter(std::shared_ptr<Link> link)
{
	return true;
}
