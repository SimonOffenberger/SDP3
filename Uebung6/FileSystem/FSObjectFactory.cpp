/*****************************************************************//**
 * \file   FSObjectFactory.cpp
 * \brief  Simple Factory class to create filesystem objects
 * 
 * \author Simon
 * \date   December 2025
 *********************************************************************/

#include "FSObjectFactory.hpp"


FSObject::Sptr FSObjectFactory::CreateFile(std::string_view name,size_t res_blocks, size_t blocksize) const
{
	return std::make_shared<File>(name, res_blocks,blocksize);
}

FSObject::Sptr FSObjectFactory::CreateFolder(std::string_view name) const
{
	return std::make_shared<Folder>(name);
}

FSObject::Sptr FSObjectFactory::CreateLink(std::string_view name, FSObject::Sptr linkedObj) const
{
	return std::make_shared<Link>(move(linkedObj),name);
}
