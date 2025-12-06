/*****************************************************************//**
 * \file Filesystem.hpp
 * \brief Filesystem class representing the root of a filesystem
 *
 * \author Simon
 * \date   November 2025
 *********************************************************************/
#ifndef FILE_SYSTEM_HPP
#define FILE_SYSTEM_HPP

#include "FSObject.hpp"
#include "IVisitor.hpp"
#include "FSObjectFactory.hpp"

class FileSystem : public Object
{
public:

	// Public Error Messages
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
	void Work(IVisitor& visitor);

	/** \brief Returns the root FSObject
	 * \return Shared pointer to root
	 */
	FSObject::Sptr ReturnRoot();

	/** \brief Set the filesystem root
	 * \param root Shared pointer to new root
	 */
	void SetRoot(FSObject::Sptr root);

	/** \brief Set the filesystem root
	 * \param root Shared pointer to new root
	 */
	void SetFactory(FSObjectFactory::Uptr Factory);

	/**
	 * \brief Creates a Test Filesystem using the Factory.
	 * \throw std::invalid_argument if Factory is nullptr.
	 */
	void CreateTestFilesystem();

private:

	FSObject::Sptr m_Root;
	FSObjectFactory::Uptr m_Factory;
};
#endif