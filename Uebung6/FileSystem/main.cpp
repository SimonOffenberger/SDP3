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


    bool TestOK = true;

    ofstream output{ "Testoutput.txt" };

    try {

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


        if (WriteOutputFile) {

            TestOK = TestOK && TestDumpVisitor(output);
            TestOK = TestOK && TestVisitor(output, dumper);
            TestOK = TestOK && TestVisitor(output, filter_link);
            TestOK = TestOK && TestVisitor(output, filter_file);
            TestOK = TestOK && TestFilterLinkVisitor(output);
            TestOK = TestOK && TestFilterFileVisitor(output);
            TestOK = TestOK && TestFactory(output);

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

		expected << "root" << std::endl
				 << "root\\sub_folder" << std::endl
			     << "root\\sub_folder\\sub_sub_folder" << std::endl
			     << "root\\sub_folder\\sub_sub_folder\\file1.txt" << std::endl;

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

		expected << "root\\sub_folder\\sub_sub_folder\\LinkToFile1 -> file1.txt" << std::endl;

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

        expected << "root\\file3.txt" << std::endl
                 << "root\\sub_folder\\sub_sub_folder\\file1.txt" << std::endl;

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
        FSObj_Sptr folder = fact.CreateFolder();
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
