/*****************************************************************//**
 * \file Filesystem.cpp
 * \brief Filesystem class representing the root of a filesystem
 *
 * \author Simon
 * \date   November 2025
 *********************************************************************/

#include "Filesystem.hpp"
#include <stdexcept>
#include <algorithm>

FileSystem::FileSystem(FSObject::Sptr root)
{
	if (root == nullptr) throw std::invalid_argument(ERROR_NULLPTR);
	
	m_Root = move(root);
}
void FileSystem::Work(IVisitor& visitor)
{
	if (m_Root == nullptr) throw std::invalid_argument(ERROR_NULLPTR);

	m_Root->Accept(visitor);
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

void FileSystem::SetFactory(FSObjectFactory::Uptr Factory)
{
	if (Factory == nullptr) throw std::invalid_argument(ERROR_NULLPTR);

	m_Factory = move(Factory);
}

void FileSystem::CreateTestFilesystem()
{
	if (m_Factory == nullptr) throw std::invalid_argument(ERROR_NULLPTR);

	FSObject::Sptr root_folder = m_Factory->CreateFolder("root");
	IFolder::Sptr root_folder_ptr = root_folder->AsFolder();
	FSObject::Sptr sub_folder = m_Factory->CreateFolder("sub");
	IFolder::Sptr sub_folder_ptr = sub_folder->AsFolder();
	FSObject::Sptr sub_sub_folder = m_Factory->CreateFolder("sub");
	IFolder::Sptr sub_sub_folder_ptr = sub_sub_folder->AsFolder();

	sub_folder->SetName("sub_folder");
	sub_sub_folder->SetName("sub_sub_folder");

	root_folder->SetName("root");
	root_folder_ptr->Add(m_Factory->CreateFile("file1.txt", 2048));
	root_folder_ptr->Add(m_Factory->CreateFile("file2.txt", 2048));
	root_folder_ptr->Add(m_Factory->CreateFile("file3.txt", 2048));
	root_folder_ptr->Add(m_Factory->CreateFile("file4.txt", 2048));
	root_folder_ptr->Add(sub_folder);
	sub_folder_ptr->Add(m_Factory->CreateFile("file5.txt", 8192));
	sub_folder_ptr->Add(m_Factory->CreateFile("file6.txt", 32768));
	sub_folder_ptr->Add(sub_sub_folder);
	sub_sub_folder_ptr->Add(m_Factory->CreateFile("file7.txt", 12288));
	sub_sub_folder_ptr->Add(m_Factory->CreateLink("LinkToRoot", root_folder));

	m_Root = move(root_folder);
}
