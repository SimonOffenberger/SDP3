/*****************************************************************//**
 * \file   FilterLinkVisitor.cpp
 * \brief  Visitor that filters links in the filesystem
 *
 * \author Simon
 * \date   December 2025
 *********************************************************************/
#include "FilterLinkVisitor.hpp"
#include <cassert>

/** \brief Files are not accepted by link filter */
bool FilterLinkVisitor::DoFilter(const std::shared_ptr<const File>& file) const
{
	assert(file != nullptr);
	return false;
}

/** \brief Links are accepted by link filter */
bool FilterLinkVisitor::DoFilter(const std::shared_ptr<const Link>& link) const
{
	assert(link != nullptr);
	return true;
}
