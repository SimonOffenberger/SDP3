/*****************************************************************//**
 * \file FSObject.hpp
 * \brief Base class for filesystem objects
 *
 * \author Simon
 * \date   November 2025
 *********************************************************************/
#ifndef FS_OBJECT_HPP
#define FS_OBJECT_HPP

#include "Object.h"
#include "IVisitor.hpp"
#include "IFolder.hpp"
#include "ILink.hpp"

#include <memory>
#include <vector>

class FSObject : public Object
{
public:
	// Public Error Messages
	inline static const std::string ERROR_NULLPTR = "ERROR Nullptr";
    inline static const std::string ERROR_STRING_EMPTY = "ERROR String Empty";

	// Smart pointer types
	using Sptr = std::shared_ptr<FSObject>;
	using Uptr = std::unique_ptr<FSObject>;
	using Wptr = std::weak_ptr<FSObject>;

	/** \brief Accept a visitor (pure virtual)
	 * \param visit Visitor to accept
	 */
	virtual void Accept(IVisitor& visit) =0;

	/** \brief Clones it self as a new 
	 *  \return Shared pointer to the cloned FSObject
	 */
	virtual FSObj_Sptr Clone() const = 0;
	
	/** \brief Try to "cast" this FSObject to a folder
	 * \return Shared pointer to IFolder or nullptr
	 */
	virtual IFolder::Sptr AsFolder();

	/** \brief Try to "cast" this FSObject to a folder
	 * \return Shared pointer to IFolder or nullptr
	 */
	virtual std::shared_ptr<const IFolder> AsFolder() const;

	/** \brief Try to cast this FSObject to a link
	 * \return Shared pointer to ILink or nullptr
	 */
	virtual std::shared_ptr<const ILink> AsLink() const;

	/** \brief Get the name of the object
	 * \return Name as std::string_view
	 */
	std::string_view GetName() const;

	/** \brief Set the name of the object
	 * \param name New name
	 */
	void SetName(std::string_view name);


	/** \brief Get parent as weak pointer
	 * \return Weak pointer to parent
	 */
	FSObj_Wptr GetParent() const;

	/** \brief Set parent of this FSObject
	 * \param parent Shared pointer to parent FSObject
	 */
	void SetParent(Sptr parent);

protected:
	/** \brief Construct an FSObject with optional name
	 * \param name Name of the FSObject
	 */
	FSObject(std::string_view name = "");


private:
	std::string m_Name;
	FSObj_Wptr m_Parent;
};

#endif
