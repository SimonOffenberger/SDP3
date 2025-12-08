/*****************************************************************//**
 * \file   main.cpp
 * \brief  Testdriver for the filesystem
 * 
 * \author Simon
 * \date   December 2025
 *********************************************************************/

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
#include <cassert>
#include <sstream>
#include "Test.hpp"
#include "fstream"
#include "vld.h"

using namespace std;

#define WriteOutputFile ON

static bool TestDumpVisitor(ostream& ost);
static bool TestFilterLinkVisitor(ostream& ost);
static bool TestFilterFileVisitor(ostream& ost);
static bool TestVisitor(ostream& ost,IVisitor & visit);
static bool TestFactory(ostream& ost);
static bool TestLink(ostream& ost);
static bool TestFolder(ostream& ost);
static bool TestFile(ostream& ost);
static bool TestFileSystem(ostream& ost);

int main()
{

    ofstream output{ "Testoutput.txt" };

    try {
	    DumpVisitor visitor(std::cout);

	    FilterLinkVisitor filter_link_visitor;

	    FilterFileVisitor filter_file_visitor(4096, 16384);

	    FileSystem homework;

	    homework.SetFactory(std::make_unique<FSObjectFactory>());
	    homework.CreateTestFilesystem();

	    homework.Work(visitor);

	    std::cout <<"-----------------------------------" << std::endl;
        homework.Work(filter_link_visitor);

	    filter_link_visitor.DumpFiltered(std::cout);

	    std::cout << "-----------------------------------" << std::endl;

        homework.Work(filter_file_visitor);

	    filter_file_visitor.DumpFiltered(std::cout);


        bool TestOK = true;

        DumpVisitor dumper{ cout };
        FilterLinkVisitor filter_link;
        FilterFileVisitor filter_file(0, 1024);

        TestOK = TestOK && TestDumpVisitor(cout);
        TestOK = TestOK && TestVisitor(cout, dumper);
        TestOK = TestOK && TestVisitor(cout, filter_link);
        TestOK = TestOK && TestVisitor(cout, filter_file);
        TestOK = TestOK && TestFilterLinkVisitor(cout);
        TestOK = TestOK && TestFilterFileVisitor(cout);
        TestOK = TestOK && TestFactory(cout);
        TestOK = TestOK && TestLink(cout);
        TestOK = TestOK && TestFolder(cout);
        TestOK = TestOK && TestFile(cout);
        TestOK = TestOK && TestFileSystem(cout);

        if (WriteOutputFile) {

            TestOK = TestOK && TestDumpVisitor(output);
            TestOK = TestOK && TestVisitor(output, dumper);
            TestOK = TestOK && TestVisitor(output, filter_link);
            TestOK = TestOK && TestVisitor(output, filter_file);
            TestOK = TestOK && TestFilterLinkVisitor(output);
            TestOK = TestOK && TestFilterFileVisitor(output);
            TestOK = TestOK && TestFactory(output);
            TestOK = TestOK && TestLink(output);
            TestOK = TestOK && TestFolder(output);
            TestOK = TestOK && TestFile(output);
            TestOK = TestOK && TestFileSystem(output);

            if (TestOK) {
                output << TestCaseOK;
            }
            else {
                output << TestCaseFail;
            }

            output.close();
        }

        if (TestOK) {
            cout << TestCaseOK;
        }
        else {
            cout << TestCaseFail;
        }
    }
    catch (const string& err) {
        cerr << err << TestCaseFail;
    }
    catch (bad_alloc const& error) {
        cerr << error.what() << TestCaseFail;
    }
    catch (const exception& err) {
        cerr << err.what() << TestCaseFail;
    }
    catch (...) {
        cerr << "Unhandelt Exception" << TestCaseFail;
    }

    if (output.is_open()) output.close();

	return 0;
};

bool TestDumpVisitor(ostream & ost)
{
    assert(ost.good());
    ost << TestStart;

    bool TestOK = true;
    string error_msg;

    try {
		FSObjectFactory factory;
		FSObject::Sptr root_folder = factory.CreateFolder("root");
		FSObject::Sptr sub_folder = factory.CreateFolder("sub_folder");
		FSObject::Sptr sub_sub_folder = factory.CreateFolder("sub_sub_folder");
		sub_sub_folder->AsFolder()->Add(File::Sptr{make_shared<File>("file1.txt", 2048)});
		sub_folder->AsFolder()->Add(sub_sub_folder);
		root_folder->AsFolder()->Add(sub_folder);

		stringstream result;
		stringstream expected;

		DumpVisitor dumper(result);

		root_folder->Accept(dumper);

		expected  << "|---[root/]\n"
                  << "|  |---[sub_folder/]\n"
                  << "|  |  |---[sub_sub_folder/]\n"
                  << "|  |  |  |---[file1.txt]\n";

		TestOK = TestOK && check_dump(ost, "DumpVisitor Test", expected.str(), result.str());

    }
    catch (const string& err) {
        error_msg = err;
    }
    catch (bad_alloc const& error) {
        error_msg = error.what();
    }
    catch (const exception& err) {
        error_msg = err.what();
    }
    catch (...) {
        error_msg = "Unhandelt Exception";
    }

    TestOK = TestOK && check_dump(ost, "Test Exception in TestCase", true, error_msg.empty());
    error_msg.clear();

    try {
		
		FSObjectFactory factory;
		FSObject::Sptr root_folder = factory.CreateFolder("root");
		
		stringstream result;

		result.setstate(ios::badbit);

		DumpVisitor dumper(result);

		root_folder->Accept(dumper); // <= sould throw Exception bad Ostream

    }
    catch (const string& err) {
        error_msg = err;
    }
    catch (bad_alloc const& error) {
        error_msg = error.what();
    }
    catch (const exception& err) {
        error_msg = err.what();
    }
    catch (...) {
        error_msg = "Unhandelt Exception";
    }

    TestOK = TestOK && check_dump(ost, "Test Exception Bad Ostream in DumpVisitor", DumpVisitor::ERROR_BAD_OSTREAM, error_msg);
    error_msg.clear();

    ost << TestEnd;

    return TestOK;
}

bool TestFilterLinkVisitor(ostream& ost)
{
    assert(ost.good());

    ost << TestStart;

    bool TestOK = true;
    string error_msg;


    try {
        FSObjectFactory factory;
        FSObject::Sptr root_folder = factory.CreateFolder("root");
        FSObject::Sptr sub_folder = factory.CreateFolder("sub_folder");
        FSObject::Sptr sub_sub_folder = factory.CreateFolder("sub_sub_folder");
        File::Sptr file = make_shared<File>("file1.txt", 2048);
        Link::Sptr link = make_shared<Link>(file,"LinkToFile1");
        sub_sub_folder->AsFolder()->Add(file );
        sub_sub_folder->AsFolder()->Add(link);
        sub_folder->AsFolder()->Add(sub_sub_folder);
        root_folder->AsFolder()->Add(sub_folder);

		FilterLinkVisitor link_filter;

		root_folder->Accept(link_filter);

		TestOK = TestOK && check_dump(ost, "FilterLinkVisitor Test filtered amount", static_cast<size_t>(1), link_filter.GetFilteredObjects().size());
		TestOK = TestOK && check_dump(ost, "FilterLinkVisitor Test filtered obj", link->GetReferncedFSObject()->GetName(), link_filter.GetFilteredObjects().cbegin()->lock()->AsLink()->GetReferncedFSObject()->GetName());

        stringstream result;
		stringstream expected;

		link_filter.DumpFiltered(result);

		expected << "\\root\\sub_folder\\sub_sub_folder\\LinkToFile1 -> file1.txt" << std::endl;

		TestOK = TestOK && check_dump(ost, "Filter Link Visitor Test Dump ", expected.str(), result.str());

    }
    catch (const string& err) {
        error_msg = err;
    }
    catch (bad_alloc const& error) {
        error_msg = error.what();
    }
    catch (const exception& err) {
        error_msg = err.what();
    }
    catch (...) {
        error_msg = "Unhandelt Exception";
    }

    TestOK = TestOK && check_dump(ost, "Test for Exception in Testcase", true, error_msg.empty());
    error_msg.clear();

    try {

        FilterLinkVisitor link_filter{};

        stringstream result;
		result.setstate(ios::badbit);

		link_filter.DumpFiltered(result);
    }
    catch (const string& err) {
        error_msg = err;
    }
    catch (bad_alloc const& error) {
        error_msg = error.what();
    }
    catch (const exception& err) {
        error_msg = err.what();
    }
    catch (...) {
        error_msg = "Unhandelt Exception";
    }

    TestOK = TestOK && check_dump(ost, "Test for Exception in Dump with bad Ostream", error_msg, FilterLinkVisitor::ERROR_BAD_OSTREAM);
    error_msg.clear();


    ost << TestEnd;

    return TestOK;
}

bool TestFilterFileVisitor(ostream& ost)
{
    assert(ost.good());

    ost << TestStart;

    bool TestOK = true;
    string error_msg;


    try {
        FSObjectFactory factory;
        FSObject::Sptr root_folder = factory.CreateFolder("root");
        FSObject::Sptr sub_folder = factory.CreateFolder("sub_folder");
        FSObject::Sptr sub_sub_folder = factory.CreateFolder("sub_sub_folder");
        File::Sptr file = make_shared<File>("file1.txt", 10);
        File::Sptr file1 = make_shared<File>("file2.txt", 10);
        File::Sptr file2 = make_shared<File>("file3.txt", 10);
        File::Sptr file3 = make_shared<File>("file4.txt", 10);
        Link::Sptr link = make_shared<Link>(file, "LinkToFile1");

		file->Write(8192);   
		file1->Write(4096);   
		file2->Write(6000);   
		file3->Write(1000); 

        sub_sub_folder->AsFolder()->Add(file);
        root_folder->AsFolder()->Add(file2);
        sub_sub_folder->AsFolder()->Add(link);
        sub_folder->AsFolder()->Add(sub_sub_folder);
        sub_folder->AsFolder()->Add(file3);
        root_folder->AsFolder()->Add(sub_folder);
        root_folder->AsFolder()->Add(file1);

        FilterFileVisitor file_filter(5000,9000);

        root_folder->Accept(file_filter);

        TestOK = TestOK && check_dump(ost, "FilterFileVisitor Test filtered amount", static_cast<size_t>(2), file_filter.GetFilteredObjects().size());
        TestOK = TestOK && check_dump(ost, "FilterFileVisitor Test for filtered file", file2->GetName(), file_filter.GetFilteredObjects().cbegin()->lock()->GetName());
        TestOK = TestOK && check_dump(ost, "FilterFileVisitor Test for filtered file", file->GetName(), file_filter.GetFilteredObjects().crbegin()->lock()->GetName());

        stringstream result;
        stringstream expected;

        file_filter.DumpFiltered(result);

        expected << "\\root\\file3.txt" << std::endl
                 << "\\root\\sub_folder\\sub_sub_folder\\file1.txt" << std::endl;

        TestOK = TestOK && check_dump(ost, "Filter File Visitor Test Dump ", expected.str(), result.str());

    }
    catch (const string& err) {
        error_msg = err;
    }
    catch (bad_alloc const& error) {
        error_msg = error.what();
    }
    catch (const exception& err) {
        error_msg = err.what();
    }
    catch (...) {
        error_msg = "Unhandelt Exception";
    }

    TestOK = TestOK && check_dump(ost, "Test for Exception in Testcase", true, error_msg.empty());
    error_msg.clear();

    try {

        FilterFileVisitor file_filter{1,2};

        stringstream result;
        result.setstate(ios::badbit);

        file_filter.DumpFiltered(result);
    }
    catch (const string& err) {
        error_msg = err;
    }
    catch (bad_alloc const& error) {
        error_msg = error.what();
    }
    catch (const exception& err) {
        error_msg = err.what();
    }
    catch (...) {
        error_msg = "Unhandelt Exception";
    }

    TestOK = TestOK && check_dump(ost, "Test for Exception in Dump with bad Ostream", error_msg, FilterLinkVisitor::ERROR_BAD_OSTREAM);
    error_msg.clear();
    
    try {

		FilterFileVisitor file_filter{ 2,1 }; // <= should throw invalid size range
    }
    catch (const string& err) {
        error_msg = err;
    }
    catch (bad_alloc const& error) {
        error_msg = error.what();
    }
    catch (const exception& err) {
        error_msg = err.what();
    }
    catch (...) {
        error_msg = "Unhandelt Exception";
    }

    TestOK = TestOK && check_dump(ost, "Test for Exception in Filter File Visiter CTOR", error_msg, FilterFileVisitor::ERROR_INVALID_SIZE_RANGE);
    error_msg.clear();


    ost << TestEnd;

    return TestOK;
}

bool TestVisitor(ostream& ost, IVisitor& visit)
{
    assert(ost.good());

    ost << TestStart;

    bool TestOK = true;
    string error_msg;


    try {

        stringstream result;

        File::Sptr file = nullptr;

        visit.Visit(file); // <= sould throw Exception Nullptr

    }
    catch (const string& err) {
        error_msg = err;
    }
    catch (bad_alloc const& error) {
        error_msg = error.what();
    }
    catch (const exception& err) {
        error_msg = err.what();
    }
    catch (...) {
        error_msg = "Unhandelt Exception";
    }

    TestOK = TestOK && check_dump(ost, "Test Exception nullptr in Visit File", DumpVisitor::ERROR_NULLPTR, error_msg);
    error_msg.clear();

    try {

        stringstream result;

        Folder::Sptr folder = nullptr;

        visit.Visit(folder); // <= sould throw Exception Nullptr

    }
    catch (const string& err) {
        error_msg = err;
    }
    catch (bad_alloc const& error) {
        error_msg = error.what();
    }
    catch (const exception& err) {
        error_msg = err.what();
    }
    catch (...) {
        error_msg = "Unhandelt Exception";
    }

    TestOK = TestOK && check_dump(ost, "Test Exception nullptr in Visit Folder", DumpVisitor::ERROR_NULLPTR, error_msg);
    error_msg.clear();

    try {

        stringstream result;

        Link::Sptr lnk = nullptr;

        visit.Visit(lnk); // <= sould throw Exception Nullptr

    }
    catch (const string& err) {
        error_msg = err;
    }
    catch (bad_alloc const& error) {
        error_msg = error.what();
    }
    catch (const exception& err) {
        error_msg = err.what();
    }
    catch (...) {
        error_msg = "Unhandelt Exception";
    }

    TestOK = TestOK && check_dump(ost, "Test Exception nullptr in Visit Link", DumpVisitor::ERROR_NULLPTR, error_msg);
    error_msg.clear();

    ost << TestEnd;

    return TestOK;
}

bool TestFactory(ostream& ost)
{
    assert(ost.good());

    ost << TestStart;

    bool TestOK = true;
    string error_msg;


    try {
        FSObjectFactory fact;
        FSObj_Sptr file = fact.CreateFile("file1.txt",10);
        FSObj_Sptr folder = fact.CreateFolder("root");
        FSObj_Sptr lnk = fact.CreateLink("link to file",file);


        TestOK = TestOK && check_dump(ost, "Test if file was constructed", true, file != nullptr);
        TestOK = TestOK && check_dump(ost, "Test if Link was constructed", true, lnk->AsLink() != nullptr);
        TestOK = TestOK && check_dump(ost, "Test if Folder was constructed", true, folder->AsFolder() != nullptr);

    }
    catch (const string& err) {
        error_msg = err;
    }
    catch (bad_alloc const& error) {
        error_msg = error.what();
    }
    catch (const exception& err) {
        error_msg = err.what();
    }
    catch (...) {
        error_msg = "Unhandelt Exception";
    }

    TestOK = TestOK && check_dump(ost, "Test for Execption in Tesstcase", true, error_msg.empty());
    error_msg.clear();

    try {
        FSObjectFactory fact;
        File::Sptr file= nullptr;
        FSObj_Sptr Lnk = fact.CreateLink("Link to File", file);

    }
    catch (const string& err) {
        error_msg = err;
    }
    catch (bad_alloc const& error) {
        error_msg = error.what();
    }
    catch (const exception& err) {
        error_msg = err.what();
    }
    catch (...) {
        error_msg = "Unhandelt Exception";
    }

    TestOK = TestOK && check_dump(ost, "Test Exception nullptr CTOR Link", Link::ERROR_NULLPTR, error_msg);
    error_msg.clear();

    ost << TestEnd;

    return TestOK;
}

bool TestLink(ostream& ost)
{
    assert(ost.good());

    ost << TestStart;

    bool TestOK = true;
    string error_msg;

    // test normal operation
    try
    {
        std::string_view folder_name = "MyFolder";
        std::string_view link_name = "LinkToMyFolder";
        Folder::Sptr folder = make_shared<Folder>(folder_name);
        Link::Sptr link = make_shared<Link>(folder, link_name);

        TestOK = TestOK && check_dump(ost, "Test normal CTOR Link", folder_name, link->GetReferncedFSObject()->GetName());
        TestOK = TestOK && check_dump(ost, "Test normal CTOR Link", link_name, link->GetName());

    }
    catch (const string& err) {
        error_msg = err;
    }
    catch (bad_alloc const& error) {
        error_msg = error.what();
    }
    catch (const exception& err) {
        error_msg = err.what();
    }
    catch (...) {
        error_msg = "Unhandelt Exception";
    }

    TestOK = TestOK && check_dump(ost, "Test normal CTOR Link - error buffer", true, error_msg.empty());
    error_msg.clear();

    // test Copy CTOR of Link
    try
    {
        std::string_view folder_name = "MyFolder";
        std::string_view link_name = "LinkToMyFolder";
        Folder::Sptr folder = make_shared<Folder>(folder_name);
        Link::Sptr link = make_shared<Link>(folder, link_name);
    
		// Call Copy CTOR
        Link::Sptr link_copy = make_shared<Link>( *link );

        TestOK = TestOK && check_dump(ost, "Test Copy CTOR of Link", link->GetReferncedFSObject(), link_copy->GetReferncedFSObject());

		// modify copied link referenced FSObject name
		link_copy->GetReferncedFSObject()->SetName("NewFolderName");

        TestOK = TestOK && check_dump(ost, "Test for shallow Copy of Link", link->GetReferncedFSObject(), link_copy->GetReferncedFSObject());
    }
    catch (const string& err) {
        error_msg = err;
    }
    catch (bad_alloc const& error) {
        error_msg = error.what();
    }
    catch (const exception& err) {
        error_msg = err.what();
    }
    catch (...) {
        error_msg = "Unhandelt Exception";
    }

    TestOK = TestOK && check_dump(ost, "Test normal COPY CTOR Link - error buffer", true, error_msg.empty());
    error_msg.clear();

    // test Assign Op of Link
    try
    {
        std::string_view folder_name = "MyFolder";
        std::string_view link_name = "LinkToMyFolder";
        Folder::Sptr folder = make_shared<Folder>(folder_name);
        Link::Sptr link = make_shared<Link>(folder, link_name);
    
        Link::Sptr link_ass = make_shared<Link>(folder, "Ass Link");
            
        *link_ass = *link;

        TestOK = TestOK && check_dump(ost, "Test Assign Op of Link", link->GetReferncedFSObject(), link_ass->GetReferncedFSObject());

    }
    catch (const string& err) {
        error_msg = err;
    }
    catch (bad_alloc const& error) {
        error_msg = error.what();
    }
    catch (const exception& err) {
        error_msg = err.what();
    }
    catch (...) {
        error_msg = "Unhandelt Exception";
    }

    TestOK = TestOK && check_dump(ost, "Test Assing Op Link - error buffer", true, error_msg.empty());
    error_msg.clear();

    // test Self Assign of Link
    try
    {
        std::string_view folder_name = "MyFolder";
        std::string_view link_name = "LinkToMyFolder";
        Folder::Sptr folder = make_shared<Folder>(folder_name);
        Link::Sptr link = make_shared<Link>(folder, link_name);

        *link = *link; // <= could throw
    }
    catch (const string& err) {
        error_msg = err;
    }
    catch (bad_alloc const& error) {
        error_msg = error.what();
    }
    catch (const exception& err) {
        error_msg = err.what();
    }
    catch (...) {
        error_msg = "Unhandelt Exception";
    }

    TestOK = TestOK && check_dump(ost, "Test Self Assing Op Link - error buffer", true, error_msg.empty());
    error_msg.clear();

    // test link to nullptr
    try
    {
        Link::Sptr link = make_shared<Link>(nullptr, "LinkToNothing");
    }
    catch (const string& err) {
        error_msg = err;
    }
    catch (bad_alloc const& error) {
        error_msg = error.what();
    }
    catch (const exception& err) {
        error_msg = err.what();
    }
    catch (...) {
        error_msg = "Unhandelt Exception";
    }

    TestOK = TestOK && check_dump(ost, "Test Exception nullptr CTOR Link", Link::ERROR_NULLPTR, error_msg);
    error_msg.clear();

    // test Link with empty string
    try
    {
        File::Sptr file = make_shared<File>("file1.txt", 2048);
        Link::Sptr link = make_shared<Link>(file, "");
    }
    catch (const string& err) {
        error_msg = err;
    }
    catch (bad_alloc const& error) {
        error_msg = error.what();
    }
    catch (const exception& err) {
        error_msg = err.what();
    }
    catch (...) {
        error_msg = "Unhandelt Exception";
    }

    TestOK = TestOK && check_dump(ost, "Test Exception empty string CTOR Link", Link::ERROR_STRING_EMPTY, error_msg);
    error_msg.clear();


    // test Link GetReferencedFSObject
    try
    {
        File::Sptr file = make_shared<File>("file1.txt", 2048);
        Link::Sptr link = make_shared<Link>(file, file->GetName());

        FSObj_Sptr ref = link->GetReferncedFSObject();// <= should be File not Folder

        TestOK = TestOK && check_dump(ost, "Test GetReferencedFSObject", file->GetName(), ref->GetName());
    }
    catch (const string& err) {
        error_msg = err;
    }
    catch (bad_alloc const& error) {
        error_msg = error.what();
    }
    catch (const exception& err) {
        error_msg = err.what();
    }
    catch (...) {
        error_msg = "Unhandelt Exception";
    }

    TestOK = TestOK && check_dump(ost, "Empty error buffer", true, error_msg.empty());
    error_msg.clear();

    // Link to a Link (chained links)
    try
    {
        File::Sptr file = make_shared<File>("original.txt", 2048);
        Link::Sptr link1 = make_shared<Link>(file, "Link1");
        Link::Sptr link2 = make_shared<Link>(link1, "Link2");

        TestOK = TestOK && check_dump(ost, "Test chained links",
            link1->GetName(), link2->GetReferncedFSObject()->GetName());
    }
    catch (const exception& err) {
        error_msg = err.what();
    }
    TestOK = TestOK && check_dump(ost, "Test chained links - error buffer", true, error_msg.empty());
    error_msg.clear();

    //Link when referenced object is destroyed (weak_ptr expiration)
    try
    {
        Link::Sptr link;
        {
            File::Sptr file = make_shared<File>("temp.txt", 2048);
            link = make_shared<Link>(file, "LinkToTemp");
            TestOK = TestOK && check_dump(ost, "Test link before destruction",
                true, link->GetReferncedFSObject() != nullptr);
        } // file goes out of scope here

        FSObj_Sptr expired_ref = link->GetReferncedFSObject();
        TestOK = TestOK && check_dump(ost, "Test link after object destruction",
            true, expired_ref == nullptr);
    }
    catch (const exception& err) {
        error_msg = err.what();
    }
    TestOK = TestOK && check_dump(ost, "Test weak_ptr expiration - error buffer", true, error_msg.empty());
    error_msg.clear();

    //AsLink() method returns valid pointer
    try
    {
        File::Sptr file = make_shared<File>("file.txt", 2048);
        Link::Sptr link = make_shared<Link>(file, "TestLink");

        std::shared_ptr<const ILink> ilink = link->AsLink();
        TestOK = TestOK && check_dump(ost, "Test AsLink() returns valid pointer",
            true, ilink != nullptr);
        TestOK = TestOK && check_dump(ost, "Test AsLink() reference matches",
            file->GetName(), ilink->GetReferncedFSObject()->GetName());
    }
    catch (const exception& err) {
        error_msg = err.what();
    }
    TestOK = TestOK && check_dump(ost, "Test AsLink() - error buffer", true, error_msg.empty());
    error_msg.clear();

    //Link SetName functionality
    try
    {
        File::Sptr file = make_shared<File>("file.txt", 2048);
        Link::Sptr link = make_shared<Link>(file, "OriginalName");

        link->SetName("NewName");
        TestOK = TestOK && check_dump(ost, "Test Link SetName",
            string_view("NewName"), link->GetName());
    }
    catch (const exception& err) {
        error_msg = err.what();
    }
    TestOK = TestOK && check_dump(ost, "Test SetName - error buffer", true, error_msg.empty());
    error_msg.clear();

    //Link SetName with empty string (should throw)
    try
    {
        File::Sptr file = make_shared<File>("file.txt", 2048);
        Link::Sptr link = make_shared<Link>(file, "OriginalName");
        link->SetName(""); // should throw
    }
    catch (const exception& err) {
        error_msg = err.what();
    }
    TestOK = TestOK && check_dump(ost, "Test Link SetName empty string",
        FSObject::ERROR_STRING_EMPTY, error_msg);
    error_msg.clear();

    // Link Accept visitor
    try
    {
        File::Sptr file = make_shared<File>("file.txt", 2048);
        Link::Sptr link = make_shared<Link>(file, "TestLink");
        stringstream result;
        DumpVisitor visitor(result);

        link->Accept(visitor);
        TestOK = TestOK && check_dump(ost, "Test Link Accept visitor - not empty",
            false, result.str().empty());
    }
    catch (const exception& err) {
        error_msg = err.what();
    }
    TestOK = TestOK && check_dump(ost, "Test Link Accept - error buffer", true, error_msg.empty());
    error_msg.clear();

    ost << TestEnd;
    return TestOK;
}
bool TestFolder(ostream& ost)
{
    assert(ost.good());

    ost << TestStart;

    bool TestOK = true;
    string error_msg;

    // test folder as intended
    try
    {
        string_view folder_name = "MyFolder";
        Folder::Sptr folder = make_shared<Folder>(folder_name);
        TestOK = TestOK && check_dump(ost, "Test normal CTOR Folder", folder_name, folder->GetName());

        File::Sptr file1 = make_shared<File>("file1.txt", 2048);
        File::Sptr file2 = make_shared<File>("file2.txt", 4096);
        
        folder->Add(file1);
        folder->Add(file2);

        FSObject::Sptr err_file = folder->GetChild(2); // <= should be nullptr
        FSObject::Sptr shared_null = nullptr;

        TestOK = TestOK && check_dump(ost, "Get Child from folder", static_pointer_cast<FSObject>(file1), folder->GetChild(0));
        TestOK = TestOK && check_dump(ost, "Get next Child from folder", static_pointer_cast<FSObject>(file2), folder->GetChild(1));
        TestOK = TestOK && check_dump(ost, "Get Child for invalid index", err_file, shared_null);
    }
    catch (const string& err) {
        error_msg = err;
    }
    catch (bad_alloc const& error) {
        error_msg = error.what();
    }
    catch (const exception& err) {
        error_msg = err.what();
    }
    catch (...) {
        error_msg = "Unhandelt Exception";
    }

    TestOK = TestOK && check_dump(ost, "Test Folder - error buffer", error_msg.empty(), true);
    error_msg.clear();

    // test Copy Ctor of Folder
    try
    {
        string_view folder_name = "MyFolder";
        Folder::Sptr folder = make_shared<Folder>( folder_name );
        File::Sptr file1 = make_shared<File>("file1.txt", 2048);
        File::Sptr file2 = make_shared<File>("file2.txt", 4096);
        
        folder->Add(file1);
        folder->Add(file2);

		// Call Copy Ctor
        Folder::Sptr folder_copy = make_shared<Folder>(*folder);

		TestOK = TestOK && check_dump(ost, "Test Copy Ctor Folder - Child 0", file1->GetName(), folder_copy->GetChild(0)->GetName());

		file1->SetName("modified_file1.txt");

		TestOK = TestOK && check_dump(ost, "Test Copy Ctor Folder test for Deep Copy", true,file1->GetName() !=folder_copy->GetChild(0)->GetName());

    }
    catch (const string& err) {
        error_msg = err;
    }
    catch (bad_alloc const& error) {
        error_msg = error.what();
    }
    catch (const exception& err) {
        error_msg = err.what();
    }
    catch (...) {
        error_msg = "Unhandelt Exception";
    }

    TestOK = TestOK && check_dump(ost, "Test Folder - error buffer", error_msg.empty(), true);
    error_msg.clear();

	// test Assign Opterator of Folder
    try
    {
        string_view folder_name = "MyFolder";
        Folder::Sptr folder = make_shared<Folder>(folder_name);
        File::Sptr file1 = make_shared<File>("file1.txt", 2048);
        File::Sptr file2 = make_shared<File>("file2.txt", 4096);
        
        folder->Add(file1);
        folder->Add(file2);

        Folder folder_ass{ "Ass folder"};
        folder_ass = *folder;

		TestOK = TestOK && check_dump(ost, "Test Assign Op Folder - Child 0", static_pointer_cast<FSObject>(file1), folder_ass.GetChild(0));

    }
    catch (const string& err) {
        error_msg = err;
    }
    catch (bad_alloc const& error) {
        error_msg = error.what();
    }
    catch (const exception& err) {
        error_msg = err.what();
    }
    catch (...) {
        error_msg = "Unhandelt Exception";
    }

    TestOK = TestOK && check_dump(ost, "Test Folder - error buffer", error_msg.empty(), true);
    error_msg.clear();

	// test Assign Opterator of Folder Self Assign
    try
    {
        string_view folder_name = "MyFolder";
        Folder::Sptr folder = make_shared<Folder>(folder_name);
        File::Sptr file1 = make_shared<File>("file1.txt", 2048);
        File::Sptr file2 = make_shared<File>("file2.txt", 4096);
        
        folder->Add(file1);
        folder->Add(file2);
        *folder = *folder;

		TestOK = TestOK && check_dump(ost, "Test Self Assign Folder - Child 0", static_pointer_cast<FSObject>(file1), folder->GetChild(0));

    }
    catch (const string& err) {
        error_msg = err;
    }
    catch (bad_alloc const& error) {
        error_msg = error.what();
    }
    catch (const exception& err) {
        error_msg = err.what();
    }
    catch (...) {
        error_msg = "Unhandelt Exception";
    }

    TestOK = TestOK && check_dump(ost, "Test Folder - error buffer", error_msg.empty(), true);
    error_msg.clear();

    // test remove child
    try
    {
        Folder::Sptr folder = make_shared<Folder>("MyFolder");
        File::Sptr file1 = make_shared<File>("file1.txt", 2048);
        File::Sptr file2 = make_shared<File>("file2.txt", 4096);
        folder->Add(file1);
        folder->Add(file2);
        folder->Remove(file1);
        TestOK = TestOK && check_dump(ost, "Test Remove Child from Folder", static_pointer_cast<FSObject>(file2), folder->GetChild(0));
    }
    catch (const string& err) {
        error_msg = err;
    }
    catch (bad_alloc const& error) {
        error_msg = error.what();
    }
    catch (const exception& err) {
        error_msg = err.what();
    }
    catch (...) {
        error_msg = "Unhandelt Exception";
    }

    TestOK = TestOK && check_dump(ost, "Test Folder - error buffer", error_msg.empty(), true);
    error_msg.clear();
    
    // test add nullptr
    try
    {
        Folder::Sptr folder = make_shared<Folder>("MyFolder");
        FSObject::Sptr null_ptr = nullptr;
        folder->Add(null_ptr); // <= should throw Exception
    }
    catch (const string& err) {
        error_msg = err;
    }
    catch (bad_alloc const& error) {
        error_msg = error.what();
    }
    catch (const exception& err) {
        error_msg = err.what();
    }
    catch (...) {
        error_msg = "Unhandelt Exception";
    }

    TestOK = TestOK && check_dump(ost, "Test Folder - add nullptr", Folder::ERROR_NULLPTR, error_msg);
    error_msg.clear();

    // test Folder with empty string
    try
    {
        Folder::Sptr folder = make_shared<Folder>("");
    }
    catch (const string& err) {
        error_msg = err;
    }
    catch (bad_alloc const& error) {
        error_msg = error.what();
    }
    catch (const exception& err) {
        error_msg = err.what();
    }
    catch (...) {
        error_msg = "Unhandelt Exception";
    }

    TestOK = TestOK && check_dump(ost, "Test Folder - CTOR with empty string", FSObject::ERROR_STRING_EMPTY, error_msg);
    error_msg.clear();

    //Nested folder structure
        try
    {
        Folder::Sptr root = make_shared<Folder>("root");
        Folder::Sptr sub1 = make_shared<Folder>("sub1");
        Folder::Sptr sub2 = make_shared<Folder>("sub2");

        root->Add(sub1);
        sub1->Add(sub2);

        TestOK = TestOK && check_dump(ost, "Test nested folders - root has sub1",
            sub1, static_pointer_cast<Folder>(root->GetChild(0)));
        TestOK = TestOK && check_dump(ost, "Test nested folders - sub1 has sub2",
            sub2, static_pointer_cast<Folder>(sub1->GetChild(0)));
    }
    catch (const exception& err) {
        error_msg = err.what();
    }
    TestOK = TestOK && check_dump(ost, "Test nested folders - error buffer", true, error_msg.empty());
    error_msg.clear();

    //Parent pointer is set correctly when adding child
    try
    {
        Folder::Sptr parent = make_shared<Folder>("parent");
        File::Sptr child = make_shared<File>("child.txt", 2048);

        parent->Add(child);
        FSObj_Wptr parent_wptr = child->GetParent();
        FSObj_Sptr parent_sptr = parent_wptr.lock();

        TestOK = TestOK && check_dump(ost, "Test parent pointer set on Add",
            parent->GetName(), parent_sptr->GetName());
    }
    catch (const exception& err) {
        error_msg = err.what();
    }
    TestOK = TestOK && check_dump(ost, "Test parent pointer - error buffer", true, error_msg.empty());
    error_msg.clear();

    //Remove non-existent child (should not crash)
    try
    {
        Folder::Sptr folder = make_shared<Folder>("folder");
        File::Sptr file1 = make_shared<File>("file1.txt", 2048);
        File::Sptr file2 = make_shared<File>("file2.txt", 2048);

        folder->Add(file1);
        folder->Remove(file2); // file2 was never added

        TestOK = TestOK && check_dump(ost, "Test remove non-existent child",
            static_pointer_cast<FSObject>(file1), folder->GetChild(0));
    }
    catch (const exception& err) {
        error_msg = err.what();
    }
    TestOK = TestOK && check_dump(ost, "Test remove non-existent - error buffer", true, error_msg.empty());
    error_msg.clear();

    //Multiple children of different types
    try
    {
        Folder::Sptr folder = make_shared<Folder>("mixed");
        File::Sptr file = make_shared<File>("file.txt", 2048);
        Folder::Sptr subfolder = make_shared<Folder>("subfolder");
        Link::Sptr link = make_shared<Link>(file, "link");

        folder->Add(file);
        folder->Add(subfolder);
        folder->Add(link);

        TestOK = TestOK && check_dump(ost, "Test mixed children - file",
            static_pointer_cast<FSObject>(file), folder->GetChild(0));
        TestOK = TestOK && check_dump(ost, "Test mixed children - folder",
            static_pointer_cast<FSObject>(subfolder), folder->GetChild(1));
        TestOK = TestOK && check_dump(ost, "Test mixed children - link",
            static_pointer_cast<FSObject>(link), folder->GetChild(2));
    }
    catch (const exception& err) {
        error_msg = err.what();
    }
    TestOK = TestOK && check_dump(ost, "Test mixed children - error buffer", true, error_msg.empty());
    error_msg.clear();

    //AsFolder() returns valid pointer
    try
    {
        Folder::Sptr folder = make_shared<Folder>("test");
        IFolder::Sptr ifolder = folder->AsFolder();

        TestOK = TestOK && check_dump(ost, "Test AsFolder() returns valid pointer",
            true, ifolder != nullptr);
    }
    catch (const exception& err) {
        error_msg = err.what();
    }
    TestOK = TestOK && check_dump(ost, "Test AsFolder() - error buffer", true, error_msg.empty());
    error_msg.clear();

    //Accept visitor with children
    try
    {
        Folder::Sptr folder = make_shared<Folder>("root");
        File::Sptr file = make_shared<File>("file.txt", 2048);
        folder->Add(file);

        stringstream result;
        DumpVisitor visitor(result);
        folder->Accept(visitor);

        // Should visit both folder and file
        TestOK = TestOK && check_dump(ost, "Test Accept visits children",
            true, result.str().find("root") != string::npos &&
            result.str().find("file.txt") != string::npos);
    }
    catch (const exception& err) {
        error_msg = err.what();
    }
    TestOK = TestOK && check_dump(ost, "Test Accept visitor - error buffer", true, error_msg.empty());
    error_msg.clear();

    //SetName on folder
    try
    {
        Folder::Sptr folder = make_shared<Folder>("original");
        folder->SetName("renamed");

        TestOK = TestOK && check_dump(ost, "Test Folder SetName",
            string_view("renamed"), folder->GetName());
    }
    catch (const exception& err) {
        error_msg = err.what();
    }
    TestOK = TestOK && check_dump(ost, "Test Folder SetName - error buffer", true, error_msg.empty());
    error_msg.clear();

    ost << TestEnd;
    return TestOK;
}
bool TestFile(ostream& ost)
{
    assert(ost.good());

    ost << TestStart;

    bool TestOK = true;
    string error_msg;

    // File as intended
    try
    {
        string_view file_name = "file1.txt";
        size_t block_size = 2048;
        size_t res_blocks = 20;
        File::Sptr file = make_shared<File>(file_name, res_blocks, block_size);

        TestOK = TestOK && check_dump(ost, "Test normal CTOR File", file_name, file->GetName());
        TestOK = TestOK && check_dump(
            ost, "Test normal CTOR File - size", 
            static_cast<size_t>(0), file->GetSize());
        
        // Write to file
        size_t write_size = 4096;
        file->Write(write_size);
        TestOK = TestOK && check_dump(ost, "Test normal - write file size", write_size, file->GetSize());
    }
    catch (const string& err) {
        error_msg = err;
    }
    catch (bad_alloc const& error) {
        error_msg = error.what();
    }
    catch (const exception& err) {
        error_msg = err.what();
    }
    catch (...) {
        error_msg = "Unhandelt Exception";
    }

    TestOK = TestOK && check_dump(ost, "Test normal - error buffer empty", error_msg.empty(), true);
    error_msg.clear();

    // File Copy Ctor
    try
    {
        string_view file_name = "file1.txt";
        size_t block_size = 2048;
        size_t res_blocks = 20;
        File file = { file_name, res_blocks, block_size };
        
		File file_copy = file; // Copy ctor

        // Write to file
        size_t write_size = 4096;
        file.Write(write_size);
        TestOK = TestOK && check_dump(ost, "Test Copy Ctor ",file.GetName(), file_copy.GetName());

        TestOK = TestOK && check_dump(ost, "Test Copy Ctor ",file.GetName(), file_copy.GetName());
    }
    catch (const string& err) {
        error_msg = err;
    }
    catch (bad_alloc const& error) {
        error_msg = error.what();
    }
    catch (const exception& err) {
        error_msg = err.what();
    }
    catch (...) {
        error_msg = "Unhandelt Exception";
    }

    TestOK = TestOK && check_dump(ost, "Test normal - error buffer empty", error_msg.empty(), true);
    error_msg.clear();

	// Assign Operator is deletet because of const members!

    // File with empty string
    try
    {
        File::Sptr file = make_shared<File>("", 20, 2048);
    }
    catch (const string& err) {
        error_msg = err;
    }
    catch (bad_alloc const& error) {
        error_msg = error.what();
    }
    catch (const exception& err) {
        error_msg = err.what();
    }
    catch (...) {
        error_msg = "Unhandelt Exception";
    }

    TestOK = TestOK && check_dump(ost, "Test CTOR Empty string - error buffer empty", error_msg, File::ERROR_STRING_EMPTY);
    error_msg.clear();

    // Write multiple times
    try
    {
        File::Sptr file = make_shared<File>("multi.txt", 10, 2048);

        file->Write(1000);
        file->Write(2000);
        file->Write(3000);

        TestOK = TestOK && check_dump(ost, "Test multiple writes",
            static_cast<size_t>(6000), file->GetSize());
    }
    catch (const exception& err) {
        error_msg = err.what();
    }
    TestOK = TestOK && check_dump(ost, "Test multiple writes - error buffer", true, error_msg.empty());
    error_msg.clear();

    // Write exactly to capacity
    try
    {
        size_t blocks = 5;
        size_t blocksize = 1024;
        File::Sptr file = make_shared<File>("exact.txt", blocks, blocksize);

        file->Write(blocks * blocksize); // Write exactly to capacity

        TestOK = TestOK && check_dump(ost, "Test write to exact capacity",
            blocks * blocksize, file->GetSize());
    }
    catch (const exception& err) {
        error_msg = err.what();
    }
    TestOK = TestOK && check_dump(ost, "Test exact capacity - error buffer", true, error_msg.empty());
    error_msg.clear();

    // Write exceeds capacity (should throw)
    try
    {
        File::Sptr file = make_shared<File>("overflow.txt", 2, 1024);
        file->Write(3000); // Exceeds 2 * 1024 = 2048
    }
    catch (const exception& err) {
        error_msg = err.what();
    }
    TestOK = TestOK && check_dump(ost, "Test write exceeds capacity",
        File::ERR_OUT_OF_SPACE, error_msg);
    error_msg.clear();

    // Write zero bytes
    try
    {
        File::Sptr file = make_shared<File>("zero.txt", 10, 2048);
        file->Write(0);

        TestOK = TestOK && check_dump(ost, "Test write zero bytes",
            static_cast<size_t>(0), file->GetSize());
    }
    catch (const exception& err) {
        error_msg = err.what();
    }
    TestOK = TestOK && check_dump(ost, "Test write zero - error buffer", true, error_msg.empty());
    error_msg.clear();

    // Multiple writes approaching capacity
    try
    {
        File::Sptr file = make_shared<File>("approach.txt", 3, 1000);
        file->Write(1000);
        file->Write(1000);
        file->Write(1000); // Total = 3000, capacity = 3000

        TestOK = TestOK && check_dump(ost, "Test multiple writes to capacity",
            static_cast<size_t>(3000), file->GetSize());
    }
    catch (const exception& err) {
        error_msg = err.what();
    }
    TestOK = TestOK && check_dump(ost, "Test approach capacity - error buffer", true, error_msg.empty());
    error_msg.clear();

    // Write after reaching capacity (should throw)
    try
    {
        File::Sptr file = make_shared<File>("full.txt", 2, 1024);
        file->Write(2048); // Fill to capacity
        file->Write(1);    // Should throw
    }
    catch (const exception& err) {
        error_msg = err.what();
    }
    TestOK = TestOK && check_dump(ost, "Test write when full",File::ERR_OUT_OF_SPACE, error_msg);
    error_msg.clear();

    // File with default blocksize (4096)
    try
    {
        File::Sptr file = make_shared<File>("default.txt", 5); // Default blocksize = 4096
        file->Write(10000);

        TestOK = TestOK && check_dump(ost, "Test default blocksize", static_cast<size_t>(10000), file->GetSize());
    }
    catch (const exception& err) {
        error_msg = err.what();
    }
    TestOK = TestOK && check_dump(ost, "Test default blocksize - error buffer", true, error_msg.empty());
    error_msg.clear();

    // Accept visitor
    try
    {
        File::Sptr file = make_shared<File>("visitor.txt", 10, 2048);
        stringstream result;
        DumpVisitor visitor(result);

        file->Accept(visitor);

        TestOK = TestOK && check_dump(ost, "Test File Accept visitor", true, result.str().find("visitor.txt") != string::npos);
    }
    catch (const exception& err) {
        error_msg = err.what();
    }
    TestOK = TestOK && check_dump(ost, "Test File Accept - error buffer", true, error_msg.empty());
    error_msg.clear();

    // SetName on file
    try
    {
        File::Sptr file = make_shared<File>("old.txt", 10, 2048);
        file->SetName("new.txt");

        TestOK = TestOK && check_dump(ost, "Test File SetName",
            string_view("new.txt"), file->GetName());
    }
    catch (const exception& err) {
        error_msg = err.what();
    }
    TestOK = TestOK && check_dump(ost, "Test File SetName - error buffer", true, error_msg.empty());
    error_msg.clear();

    // File AsFolder should return nullptr
    try
    {
        File::Sptr file = make_shared<File>("notfolder.txt", 10, 2048);
        IFolder::Sptr folder_ptr = file->AsFolder();

        TestOK = TestOK && check_dump(ost, "Test File AsFolder returns nullptr", true, folder_ptr == nullptr);
    }
    catch (const exception& err) {
        error_msg = err.what();
    }
    TestOK = TestOK && check_dump(ost, "Test File AsFolder - error buffer", true, error_msg.empty());
    error_msg.clear();

    ost << TestEnd;
    return TestOK;
}

bool TestFileSystem(ostream& ost)
{
    assert(ost.good());

    ost << TestStart;

    bool TestOK = true;
    string error_msg;

    try
    {
		FileSystem fsys;
        
		fsys.SetFactory(make_unique<FSObjectFactory>());

		// build a Test filesystem using the set Factory
        fsys.CreateTestFilesystem();
        
		DumpVisitor dumper(ost);

		ost << "Dump of Test Filesystem via Dump Visitor:\n\n";

		fsys.Work(dumper);

		ost << "\n\n";
    }
    catch (const string& err) {
        error_msg = err;
    }
    catch (bad_alloc const& error) {
        error_msg = error.what();
    }
    catch (const exception& err) {
        error_msg = err.what();
    }
    catch (...) {
        error_msg = "Unhandelt Exception";
    }

    TestOK = TestOK && check_dump(ost, "Test normal op Filesystem - error buffer empty", error_msg.empty(), true);
    error_msg.clear();

    try
    {
		FileSystem fsys;


		FSObjectFactory factory;

		FSObject::Sptr root = factory.CreateFolder("root");

        fsys.SetRoot(move(root));
        
        stringstream result;
        stringstream expected;


		DumpVisitor dumper(result);
        
		fsys.Work(dumper);

        root = move(fsys.ReturnRoot());

		DumpVisitor expected_dumper(expected);

		root->Accept(expected_dumper);

		TestOK = TestOK && check_dump(ost, "Test ReturnRoot matches",
			expected.str(), result.str());

    }
    catch (const string& err) {
        error_msg = err;
    }
    catch (bad_alloc const& error) {
        error_msg = error.what();
    }
    catch (const exception& err) {
        error_msg = err.what();
    }
    catch (...) {
        error_msg = "Unhandelt Exception";
    }

    TestOK = TestOK && check_dump(ost, "Test normal op Filesystem - error buffer empty", error_msg.empty(), true);
    error_msg.clear();


    try
    {
		FileSystem fsys;
        FSObject::Sptr root = nullptr;
   
		fsys.SetRoot(move(root)); // <= should throw
    }
    catch (const string& err) {
        error_msg = err;
    }
    catch (bad_alloc const& error) {
        error_msg = error.what();
    }
    catch (const exception& err) {
        error_msg = err.what();
    }
    catch (...) {
        error_msg = "Unhandelt Exception";
    }

    TestOK = TestOK && check_dump(ost, "Test Exception Set Null Root", FileSystem::ERROR_NULLPTR ,error_msg);
    error_msg.clear();

    try
    {
		FileSystem fsys;
        FSObjectFactory::Uptr factory = nullptr;
   
        fsys.SetFactory(move(factory)); // <= should throw
    }
    catch (const string& err) {
        error_msg = err;
    }
    catch (bad_alloc const& error) {
        error_msg = error.what();
    }
    catch (const exception& err) {
        error_msg = err.what();
    }
    catch (...) {
        error_msg = "Unhandelt Exception";
    }

    TestOK = TestOK && check_dump(ost, "Test Exception Set Null Factory", FileSystem::ERROR_NULLPTR ,error_msg);
    error_msg.clear();

    try
    {
		FileSystem fsys;
   
		fsys.CreateTestFilesystem(); // <= should throw because no factory set
    }
    catch (const string& err) {
        error_msg = err;
    }
    catch (bad_alloc const& error) {
        error_msg = error.what();
    }
    catch (const exception& err) {
        error_msg = err.what();
    }
    catch (...) {
        error_msg = "Unhandelt Exception";
    }

    TestOK = TestOK && check_dump(ost, "Test Exception no Factory in Create Test FileSystem", FileSystem::ERROR_NULLPTR ,error_msg);
    error_msg.clear();

    try
    {
		FileSystem fsys;
		DumpVisitor dumper(ost);
		fsys.Work(dumper); // <= should throw because root is null
    }
    catch (const string& err) {
        error_msg = err;
    }
    catch (bad_alloc const& error) {
        error_msg = error.what();
    }
    catch (const exception& err) {
        error_msg = err.what();
    }
    catch (...) {
        error_msg = "Unhandelt Exception";
    }

    TestOK = TestOK && check_dump(ost, "Test Exception Work with no root set", FileSystem::ERROR_NULLPTR ,error_msg);
    error_msg.clear();


    ost << TestEnd;

    return TestOK;
}
