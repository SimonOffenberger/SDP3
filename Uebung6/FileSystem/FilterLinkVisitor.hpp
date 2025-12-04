/*****************************************************************//**
 * \file   FilterLinkVisitor.hpp
 * \brief  Visitor that filters links in the filesystem
 * 
 * \author Simon
 * \date   December 2025
 *********************************************************************/
#ifndef FILTER_LINK_VISITOR_HPP
#define FILTER_LINK_VISITOR_HPP

#include "FilterVisitor.hpp"

class FilterLinkVisitor : public FilterVisitor
{
public:

protected:

	/** \brief Links are accepted by this filter
	 * \param file File to check
	 * \return false always
	 */
	virtual bool DoFilter(const std::shared_ptr<const File>& file) const override;

	/** \brief Links are accepted by this filter
	 * \param link Link to check
	 * \return true if link is present
	 */
	virtual bool DoFilter(const std::shared_ptr<const Link>& link) const override;

private:
};

#endif
