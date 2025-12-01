/*****************************************************************//**
 * \file FSObjectFactory.hpp
 * \brief Simple Factory class to create filesystem objects
 *
 * \author Simon
 * \date   November 2025
 *********************************************************************/
#ifndef FS_OBJECT_FACTORY_HPP
#define FS_OBJECT_FACTORY_HPP

#include "Object.h"
#include "FSObject.hpp"
#include "Folder.hpp"
#include "File.hpp"
#include "Link.hpp"
#include <memory>


class FSObjectFactory : public Object
{
public:
	inline static const std::string ERROR_NULLPTR = "ERROR Nullptr";

	/** \brief Create a File FSObject
	 * \param name Name of the file
	 * \param res_blocks Reserved blocks
	 * \param blocksize Block size (default 4096)
	 * \return Shared pointer to created File FSObject
	 */
	FSObject::Sptr CreateFile(std::string_view name,const size_t res_blocks,const size_t blocksize = 4096) const;
	
	/** \brief Create a Folder FSObject
	 * \param name Name of the folder
	 * \return Shared pointer to created Folder FSObject
	 */
	FSObject::Sptr CreateFolder(std::string_view name = "") const;
	
	/** \brief Create a Link FSObject
	 * \param name Name of the link
	 * \param linkedObj Shared pointer to linked FSObject
	 * \return Shared pointer to created Link FSObject
	 */
	FSObject::Sptr CreateLink(std::string_view name, FSObject::Sptr linkedObj) const;

private:
};
#endif
