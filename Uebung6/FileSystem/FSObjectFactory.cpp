#include "FSObjectFactory.hpp"


FSObject::Sptr FSObjectFactory::CreateFile(std::string_view name,size_t size, size_t blocksize) const
{
	return std::make_shared<File>(name,size,blocksize);
}

FSObject::Sptr FSObjectFactory::CreateFolder() const
{
	return std::make_shared<Folder>();
}

FSObject::Sptr FSObjectFactory::CreateLink(std::string_view name, FSObject::Sptr linkedObj) const
{
	return std::make_shared<Link>(linkedObj,name);
}
