/*****************************************************************//**
 * \file   
 * \brief  
 *
 * \author Simon
 * \date   November 2025
 *********************************************************************/
#ifndef IVISITOR_HPP
#define IVISITOR_HPP

 // Forward declarations to avoid circular dependencies
class Folder;
class File;
class Link;

class IVisitor
{
public:

	virtual void Visit(const Folder & folder)=0;

	virtual void Visit(const File & file)=0;

	virtual void Visit(const Link & link)=0;

	virtual ~IVisitor() = default;

private: 
};

#endif
