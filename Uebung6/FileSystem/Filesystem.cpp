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

constexpr size_t BLOCKSIZE_SMALL = 2048;
constexpr size_t BLOCKSIZE_MEDIUM = 8192;
constexpr size_t BLOCKSIZE_LARGE = 32768;
constexpr size_t BLOCKSIZE_CUSTOM = 12288;


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
	root_folder_ptr->Add(m_Factory->CreateFile("file1.txt", BLOCKSIZE_SMALL));
	root_folder_ptr->Add(m_Factory->CreateFile("file2.txt", BLOCKSIZE_SMALL));
	root_folder_ptr->Add(m_Factory->CreateFile("file3.txt", BLOCKSIZE_SMALL));
	root_folder_ptr->Add(m_Factory->CreateFile("file4.txt", BLOCKSIZE_SMALL));
	root_folder_ptr->Add(sub_folder);
	sub_folder_ptr->Add(m_Factory->CreateFile("file5.txt", BLOCKSIZE_MEDIUM));
	sub_folder_ptr->Add(m_Factory->CreateFile("file6.txt", BLOCKSIZE_LARGE));
	sub_folder_ptr->Add(sub_sub_folder);
	sub_sub_folder_ptr->Add(m_Factory->CreateFile("file7.txt", BLOCKSIZE_CUSTOM));
	sub_sub_folder_ptr->Add(m_Factory->CreateLink("LinkToRoot", root_folder));

	m_Root = move(root_folder);
}
