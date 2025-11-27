/*****************************************************************//**
 * \file
 * \brief
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


	FSObject::Sptr CreateFile(size_t size, size_t blocksize = 4096) const;
	FSObject::Sptr CreateFolder() const;
	FSObject::Sptr CreateLink(FSObject::Sptr linkedObj) const;

private:
};
#endif
