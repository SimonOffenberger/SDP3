/*****************************************************************//**
 * \file Folder.hpp
 * \brief Folder class representing a folder in the filesystem
 *
 * \author Simon
 * \date   November 2025
 *********************************************************************/
#ifndef FOLDER_HPP
#define FOLDER_HPP

#include "IFolder.hpp"
#include "IVisitor.hpp"
#include "FSObject.hpp"

#include <memory>
#include <vector>

class Folder : public IFolder, public FSObject, public std::enable_shared_from_this<Folder>
{
public:

	// Smart pointer types
	using Uptr = std::unique_ptr<Folder>;
	using Sptr = std::shared_ptr<Folder>;
	using Wptr = std::shared_ptr<Folder>;
	using Cont = std::vector<FSObj_Sptr>;

	/** \brief Construct a folder with a name
	 * \param name Name of the folder
	 */
	Folder(std::string_view name) : FSObject(name) {}

	/** \brief Add a child FSObject to this folder
	 * \param fsobj Shared pointer to the child
	 */
	virtual void Add(FSObj_Sptr fsobj);

	/** \brief Get child by index
	 * \param idx Index (by value is faster than by reference)
	 * \return Shared pointer to child or nullptr
	 */
	virtual FSObj_Sptr GetChild(const size_t idx) override;

	/** \brief Remove a child from the folder
	 * \param fsobj Child to remove
	 */
	virtual void Remove(FSObj_Sptr fsobj);

	/** \brief Cast this FSObject to a folder interface
	 * \return Shared pointer to IFolder
	 */
	virtual IFolder::Sptr AsFolder() override;

	/** \brief Accept a visitor and propagate to children
	 * \param visit Visitor to accept
	 */
	virtual void Accept(IVisitor& visit) override;
	
private:
	Folder::Cont m_Children;
};

#endif
