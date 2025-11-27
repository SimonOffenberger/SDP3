#include "FilterLinkVisitor.hpp"

bool FilterLinkVisitor::DoFilter(const File& file)
{
	return false;
}

bool FilterLinkVisitor::DoFilter(const Link& link)
{
	return true;
}
