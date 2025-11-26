#include <iostream>
#include <string>
#include <memory>
#include "FSObject.hpp"
#include "IFolder.hpp"
#include "Folder.hpp"
#include "File.hpp"
#include "Link.hpp"


int main()
{
    // test by instantiating objects
    FSObj_Sptr file1 = std::make_shared<File>(8192);
  
    FSObj_Sptr link1 = std::make_shared<Link>(file1);
  
    // Use std::shared_ptr<Folder> directly and assign to a weak pointer
    IFolder::Sptr root_folder = std::make_shared<Folder>();
    root_folder->Add(file1);
    root_folder->Add(link1);

    FSObj_Sptr obj = root_folder->GetChild(0);
    
    obj->SetName("root");
    std::cout << obj->GetName() << std::endl;

};