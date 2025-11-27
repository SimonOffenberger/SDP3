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

#include <memory>

class IVisitor
{
public:

	virtual void Visit(std::shared_ptr<Folder> folder)=0;

	virtual void Visit(std::shared_ptr<File> file)=0;

	virtual void Visit(std::shared_ptr<Link> link)=0;

	virtual ~IVisitor() = default;

private: 
};

#endif
