/*****************************************************************//**
 * \file  IVisitor.hpp
 * \brief  Interface for visitor pattern in filesystem objects
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

	/** \brief Visit a folder
	 * \param folder Shared pointer to the folder to visit
	 */
	virtual void Visit(const std::shared_ptr<const Folder> folder)=0;

	/** \brief Visit a file
	 * \param file Shared pointer to the file to visit
	 */
	virtual void Visit(const std::shared_ptr<const File> file)=0;

	/** \brief Visit a link
	 * \param link Shared pointer to the link to visit
	 */
	virtual void Visit(const std::shared_ptr<const Link> link)=0;

	/** \brief Virtual destructor for visitor implementations */
	virtual ~IVisitor() = default;

private: 
};

#endif
