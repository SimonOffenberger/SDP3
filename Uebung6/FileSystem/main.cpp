#include <iostream>
#include <string>
#include <memory>
#include "FSObject.hpp"
#include "IFolder.hpp"
#include "Folder.hpp"
#include "File.hpp"
#include "Link.hpp"
#include "DumpVisitor.hpp"
#include "FilterFileVisitor.hpp"
#include "FilterLinkVisitor.hpp"


int main()
{
    // test by instantiating objects
    FSObj_Sptr file1 = std::make_shared<File>(8192);
	file1->SetName("file1.txt");
    FSObj_Sptr link1 = std::make_shared<Link>(file1);
	link1->SetName("link_to_file1");

    // test by instantiating objects
    FSObj_Sptr file2 = std::make_shared<File>(8192);
	file2->SetName("file2.txt");
    FSObj_Sptr link2 = std::make_shared<Link>(file1);
	link2->SetName("link_to_file2");

    // Use std::shared_ptr<Folder> directly and assign to a weak pointer
    Folder::Sptr root_folder = std::make_shared<Folder>();
	root_folder->SetName("root_folder");

	Folder::Sptr sub_folder = std::make_shared<Folder>();
	sub_folder->SetName("sub_folder");
	sub_folder->Add(file2);
	sub_folder->Add(link2);

    root_folder->Add(file1);
    root_folder->Add(link1);
	root_folder->Add(sub_folder);

    FSObj_Sptr obj = root_folder->GetChild(0);
    
    obj->SetName("root");
    std::cout << obj->GetName() << std::endl;

	DumpVisitor visitor(std::cout);

    root_folder->Accept(visitor);

	FilterLinkVisitor filter_link_visitor;

	root_folder->Accept(filter_link_visitor);

	FilterFileVisitor filter_file_visitor(4096, 16384);

	root_folder->Accept(filter_file_visitor);

	filter_link_visitor.DumpFiltered(std::cout);
	filter_file_visitor.DumpFiltered(std::cout);

};