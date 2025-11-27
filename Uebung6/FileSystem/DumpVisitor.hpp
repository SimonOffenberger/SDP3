/*****************************************************************//**
 * \file
 * \brief
 *
 * \author Simon
 * \date   November 2025
 *********************************************************************/
#ifndef DUMP_VISITOR_HPP
#define DUMP_VISITOR_HPP

#include <iostream>
#include "IVisitor.hpp"
#include "FSObject.hpp"

class DumpVisitor : public IVisitor
{
public: 

	inline static const std::string ERROR_BAD_OSTREAM = "ERROR: bad output stream";

	DumpVisitor(std::ostream& ost) : m_ost{ ost } {}

	virtual void Visit(const Folder& folder) override;

	virtual void Visit(const File& file) override;

	virtual void Visit(const Link& Link) override;

private:

	void Dump(const FSObject& fsobj);

	std::ostream & m_ost;
};

#endif
