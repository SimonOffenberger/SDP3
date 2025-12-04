#include "Filesystem.hpp"
#include <stdexcept>

FileSystem::FileSystem(FSObject::Sptr root)
{
	if (root == nullptr) throw std::invalid_argument(ERROR_NULLPTR);
	
	m_Root = move(root);
}

IVisitor& FileSystem::Work(IVisitor& visitor)
{
	if (m_Root == nullptr) throw std::invalid_argument(ERROR_NULLPTR);

	m_Root->Accept(visitor);

	return visitor;
}

FSObject::Sptr FileSystem::ReturnRoot()
{
	return move(m_Root);
}

void FileSystem::SetRoot(FSObject::Sptr root)
{
	if (root == nullptr) throw std::invalid_argument(ERROR_NULLPTR);

	m_Root = move(root);
}
