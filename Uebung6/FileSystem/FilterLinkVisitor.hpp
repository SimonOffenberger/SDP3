/*****************************************************************//**
 * \file
 * \brief
 *
 * \author Simon
 * \date   November 2025
 *********************************************************************/
#ifndef FILTER_LINK_VISITOR_HPP
#define FILTER_LINK_VISITOR_HPP

#include "FilterVisitor.hpp"

class FilterLinkVisitor : public FilterVisitor
{
public:

protected:

	virtual bool DoFilter(std::shared_ptr<File> file) override;

	virtual bool DoFilter(std::shared_ptr<Link> link) override;

private:
};

#endif
