/*****************************************************************//**
 * \file
 * \brief
 *
 * \author Simon
 * \date   November 2025
 *********************************************************************/
#ifndef FILE_SYSTEM_HPP
#define FILE_SYSTEM_HPP

#include "FSObject.hpp"
#include "IVisitor.hpp"

class FileSystem : public Object
{
public:
	inline static const std::string ERROR_NULLPTR = "ERROR Nullptr";

	FileSystem() = default;	

	/** \brief Construct a FileSystem with a root FSObject
	 * \param root Root FSObject shared pointer
	 */
	FileSystem(FSObject::Sptr root);
	
	/** \brief Walk the filesystem with a visitor
	 * \param visitor Visitor to apply
	 * \return Reference to visitor
	 */
	IVisitor& Work(IVisitor& visitor);

	/** \brief Get root FSObject
	 * \return Shared pointer to root
	 */
	FSObject::Sptr GetRoot();

	/** \brief Set the filesystem root
	 * \param root Shared pointer to new root
	 */
	void SetRoot(FSObject::Sptr root);


private:
	FSObject::Sptr m_Root;
};
#endif