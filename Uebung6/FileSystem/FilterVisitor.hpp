/*****************************************************************//**
 * \file
 * \brief
 *
 * \author Simon
 * \date   November 2025
 *********************************************************************/
#ifndef FILTER_VISITOR_HPP
#define FILTER_VISITOR_HPP

#include "IVisitor.hpp"
#include "FSObject.hpp"

#include <vector>

class FilterVisitor : public IVisitor
{
public:

	virtual void Visit(const Folder& folder) override {}

	virtual void Visit(const File& file) override;

	virtual void Visit(const Link& link) override;

	void DumpFiltered(std::ostream& ost) const;

protected: 

	virtual bool DoFilter(const File& file)=0;

	virtual bool DoFilter(const Link& link)=0;

	using TContFSobj = std::vector<const FSObject*>;

private:

	TContFSobj m_FilterCont;
};

#endif
