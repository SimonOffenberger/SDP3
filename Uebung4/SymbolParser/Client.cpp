/*****************************************************************//**
 * \file   Client.cpp
 * \brief  Test File to show that you only need to include Symbol Parser 
 * \brief  plus factories to work with the parser!
 * 
 * \author Simon
 * \date   November 2025
 *********************************************************************/

// The client is only dependent on these classes!!
#include "SymbolParser.hpp"
#include "JavaSymbolFactory.hpp"
#include "IECSymbolFactory.hpp"

// Testing Includes
#include "Test.hpp"
#include <fstream>
#include <cassert>
#include "Client.hpp"

using namespace std;

bool TestSymbolParser(std::ostream& ost)
{
    bool TestOK = true;
    string error_msg;

    if (!ost.good()) throw "Error Ostream bad!";

    ost << TestStart;

    // normal operating mode - no exception should be thrown
    try {
        SymbolParser parser{ JavaSymbolFactory::GetInstance() };
        parser.AddType("Button");
        parser.AddVariable("mButton", "Button");
        parser.SetFactory(IECSymbolFactory::GetInstance());
        parser.AddType("TYPE");
        parser.AddVariable("VARIABLE", "TYPE");
        parser.SetFactory(JavaSymbolFactory::GetInstance());
        parser.AddVariable("mButton2", "Button"); // <- this is only possible if the loading of the vars was successful
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

    TestOK = TestOK && check_dump(ost, "Normal Operating Parser", true, error_msg.empty());
    error_msg.clear();

    // addtype - adding empty type - throws error
    try {
        SymbolParser parser{ JavaSymbolFactory::GetInstance() };
        parser.AddType("");
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

    TestOK = TestOK && check_dump(ost, ".AddType() - add empty type to parser", SymbolParser::ERROR_EMPTY_STRING, error_msg);
    error_msg.clear();

    // addVariable add empty type - throws error
    try {
        SymbolParser parser{ JavaSymbolFactory::GetInstance() };
        parser.AddVariable("VarName", "");
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

    TestOK = TestOK && check_dump(ost, ".AddVariable() - add empty type to factory", SymbolParser::ERROR_EMPTY_STRING, error_msg);
    error_msg.clear();

    // addVariable add empty var - throws error
    try {
        SymbolParser parser{ JavaSymbolFactory::GetInstance() };
        parser.AddVariable("", "Type");
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

    TestOK = TestOK && check_dump(ost, ".AddVariable() - add empty var to factory", SymbolParser::ERROR_EMPTY_STRING, error_msg);
    error_msg.clear();

    // addVariable add variable for non existing type
    try {
        SymbolParser parser{ JavaSymbolFactory::GetInstance() };
        parser.AddVariable("Var", "Type");
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

    TestOK = TestOK && check_dump(ost, ".AddVariable() - add variable with nonexisting type", SymbolParser::ERROR_NONEXISTING_TYPE, error_msg);


    // addVariable add variable for non existing type
    try {
        SymbolParser parser{ JavaSymbolFactory::GetInstance() };
        parser.AddType("uint65536_t");
        parser.AddType("uint65536_t");
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

    TestOK = TestOK && check_dump(ost, ".AddType() - add duplicate type", SymbolParser::ERROR_DUPLICATE_TYPE, error_msg);
    error_msg.clear();

    // addVariable add variable for non existing type
    try {
        SymbolParser parser{ JavaSymbolFactory::GetInstance() };
        parser.AddType("uint4096_t");
        parser.AddVariable("Large_int", "uint4096_t");
        parser.AddVariable("Large_int", "uint4096_t");
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

    TestOK = TestOK && check_dump(ost, ".AddVar() - add duplicate Var", SymbolParser::ERROR_DUPLICATE_VAR, error_msg);
    error_msg.clear();



    // Test Load and Store of the SymbolParser
    try {
        SymbolParser parser{ JavaSymbolFactory::GetInstance() };
        parser.AddType("uint8192_t");
        parser.AddVariable("Large_int", "uint8192_t");
        parser.SetFactory( IECSymbolFactory::GetInstance());
        parser.AddType("ui32");
        parser.AddVariable("Hello", "ui32");
        parser.SetFactory(JavaSymbolFactory::GetInstance());
        parser.AddType("uint8192_t"); // <-- this should throw exception type already exists!!
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

    TestOK = TestOK && check_dump(ost, "Test Store and Load Java Fact with exeption Dup Type", SymbolParser::ERROR_DUPLICATE_TYPE, error_msg);
    error_msg.clear();


    // Test Load and Store of the SymbolParser
    try {
        
        SymbolParser parser{ IECSymbolFactory::GetInstance() };

        parser.AddType("ui32");

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

    TestOK = TestOK && check_dump(ost, "Test Store and Load IEC Fact with exeption Dup Type", SymbolParser::ERROR_DUPLICATE_TYPE, error_msg);
    error_msg.clear();

    ost << TestEnd;
    return TestOK;
}