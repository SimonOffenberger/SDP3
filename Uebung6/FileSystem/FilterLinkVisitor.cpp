/*****************************************************************//**
 * \file   FilterLinkVisitor.cpp
 * \brief  Visitor that filters links in the filesystem
 *
 * \author Simon
 * \date   December 2025
 *********************************************************************/
#include "FilterLinkVisitor.hpp"
#include <cassert>
#include <stdexcept>

/** \brief Files are not accepted by link filter */
bool FilterLinkVisitor::DoFilter(const std::shared_ptr<const File>& file) const
{
	if(file == nullptr) throw std::invalid_argument(ERROR_NULLPTR);
	return false;
}

/** \brief Links are accepted by link filter */
bool FilterLinkVisitor::DoFilter(const std::shared_ptr<const Link>& link) const
{
	if(link == nullptr) throw std::invalid_argument(ERROR_NULLPTR);

	return true;
}
