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

	inline static const std::string ERROR_NULLPTR = "ERROR: null pointer";

	virtual void Visit(std::shared_ptr<Folder> folder) override {}

	virtual void Visit(std::shared_ptr<File> file) override;

	virtual void Visit(std::shared_ptr<Link> link) override;

	void DumpFiltered(std::ostream& ost) const;

protected: 

	virtual bool DoFilter(std::shared_ptr<File> file)=0;

	virtual bool DoFilter(std::shared_ptr<Link> link)=0;

	using TContFSobj = std::vector<FSObj_Wptr>;

private:

	TContFSobj m_FilterCont;
};

#endif
