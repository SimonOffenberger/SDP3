#include <iostream>
#include <string>
#include <memory>
#include "FSObject.hpp"
#include "IFolder.hpp"
#include "ILink.hpp"
#include "FSObjectFactory.hpp"
#include "DumpVisitor.hpp"
#include "FilterFileVisitor.hpp"
#include "FilterLinkVisitor.hpp"
#include "Filesystem.hpp"


int main()
{
	DumpVisitor visitor(std::cout);

	FilterLinkVisitor filter_link_visitor;

	FilterFileVisitor filter_file_visitor(4096, 16384);

	FSObjectFactory factory;

	FSObject::Sptr root_folder = factory.CreateFolder();
	IFolder::Sptr root_folder_ptr = root_folder->AsFolder();
	FSObject::Sptr sub_folder = factory.CreateFolder();
	IFolder::Sptr sub_folder_ptr = sub_folder->AsFolder();
	FSObject::Sptr sub_sub_folder = factory.CreateFolder();
	IFolder::Sptr sub_sub_folder_ptr = sub_sub_folder->AsFolder();

	sub_folder->SetName("sub_folder");
	sub_sub_folder->SetName("sub_sub_folder");

	root_folder->SetName("root");
	root_folder_ptr->Add(factory.CreateFile("file1.txt", 2048));
	root_folder_ptr->Add(factory.CreateFile("file2.txt", 2048));
	root_folder_ptr->Add(factory.CreateFile("file3.txt", 2048));
	root_folder_ptr->Add(factory.CreateFile("file4.txt", 2048));
	root_folder_ptr->Add(sub_folder);
	sub_folder_ptr->Add(factory.CreateFile("file5.txt", 8192));
	sub_folder_ptr->Add(factory.CreateFile("file6.txt", 32768));
	sub_folder_ptr->Add(sub_sub_folder);
	sub_sub_folder_ptr->Add(factory.CreateFile("file7.txt", 12288));
	sub_sub_folder_ptr->Add(factory.CreateLink("LinkToRoot", root_folder));


	FileSystem homework(move(root_folder));

	homework.Work(visitor);

	std::cout <<"-----------------------------------" << std::endl;
    homework.Work(filter_link_visitor);

	filter_link_visitor.DumpFiltered(std::cout);

	std::cout << "-----------------------------------" << std::endl;

    homework.Work(filter_file_visitor);

	filter_file_visitor.DumpFiltered(std::cout);

	return 0;

};