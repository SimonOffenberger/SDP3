#include "FSObjectFactory.hpp"


FSObject::Sptr FSObjectFactory::CreateFile(size_t size, size_t blocksize) const
{
	return std::make_shared<File>(size,blocksize);
}

FSObject::Sptr FSObjectFactory::CreateFolder() const
{
	return std::make_shared<Folder>();
}

FSObject::Sptr FSObjectFactory::CreateLink(FSObject::Sptr linkedObj) const
{
	return std::make_shared<Link>(linkedObj);
}
