/*****************************************************************//**
 * \file   
 * \brief  
 *
 * \author Simon
 * \date   November 2025
 *********************************************************************/
#ifndef IVISITOR_HPP
#define IVISITOR_HPP

#include "Link.hpp"
#include "File.hpp"
#include "Folder.hpp"

class IVisitor
{
public:

	virtual void Visit(const Folder & folder)=0;

	virtual void Visit(const File & file)=0;

	virtual void Visit(const Link & Link)=0;

	virtual ~Visitor() = default;

private: 
};

#endif
