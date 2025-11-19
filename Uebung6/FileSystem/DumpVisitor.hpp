/*****************************************************************//**
 * \file
 * \brief
 *
 * \author Simon
 * \date   November 2025
 *********************************************************************/
#ifndef IVISITOR_HPP
#define IVISITOR_HPP

#include "IVisitor.hpp"

#include <iostream>

class DumpVisitor : public IVisitor
{
public:

	DumpVisitor(std::ostream& ost) : m_ost{ ost } {}

	virtual void Visit(const Folder& folder) override;

	virtual void Visit(const File& file) override;

	virtual void Visit(const Link& Link) override;

private:

	std::ostream & m_ost;
};

#endif
