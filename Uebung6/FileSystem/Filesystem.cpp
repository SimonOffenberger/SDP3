#include "Filesystem.hpp"

FileSystem::FileSystem(FSObject::Sptr root)
{
	if (root == nullptr) throw ERROR_NULLPTR;
	
	m_Root = move(root);
}

IVisitor& FileSystem::Work(IVisitor& visitor)
{
	if (m_Root == nullptr) throw ERROR_NULLPTR;

	m_Root->Accept(visitor);

	return visitor;
}

FSObject::Sptr FileSystem::ReturnRoot()
{
	return move(m_Root);
}

void FileSystem::SetRoot(FSObject::Sptr root)
{
	if (root == nullptr) throw ERROR_NULLPTR;

	m_Root = move(root);
}
