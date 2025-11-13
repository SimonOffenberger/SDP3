/*****************************************************************//**
 * \file   Main.cpp
 * \brief  Testdriver for Symbol Parser and all connected Classes
 * \author Simon
 * \date   November 2025
 *********************************************************************/

// These Includes are needed because of the testcases !!
#include "IECVariable.hpp"
#include "JavaVariable.hpp"
#include "IECType.hpp"
#include "JavaType.hpp"

// These are the Includes if the Symbolparses is used by a Client!!
#include "SymbolParser.hpp"
#include "JavaSymbolFactory.hpp"
#include "IECSymbolFactory.hpp"
#include "Client.hpp"

// Testing Includes
#include "Test.hpp"
#include "vld.h"
#include <fstream>
#include <iostream>
#include <cassert>

#include <cstdio>

using namespace std;

#define WriteOutputFile ON

static bool TestVariable(Variable* var, const string & name, Type::Sptr typ, ostream & ost = cout);
static bool TestType(Type::Sptr typ, ostream & ost = cout);
static bool TestIECVar(ostream& ost = cout);
static bool TestJavaVar(ostream& ost = cout);
static bool TestIECType(ostream& ost = cout);
static bool TestJavaType(ostream& ost = cout);



static void EraseFile(const char* path) {
    // Versucht, die Datei zu loeschen
    if (std::remove(path) == 0) {
        // Datei wurde erfolgreich geloescht
        std::printf("Datei '%s' erfolgreich geloescht.\n", path);
    }
    else {
        // Fehler beim Loeschen der Datei
        std::perror("Fehler beim Loeschen der Datei");
    }
}

int main()
{   
    // Erase previos Symbol files for test cases
    EraseFile("IECTypes.sym");
    EraseFile("IECVars.sym");
    EraseFile("JavaTypes.sym");
    EraseFile("JavaVars.sym");


    bool TestOK = true;

    ofstream output{ "output.txt" };


    try {
        Type::Sptr Itype{ make_shared<IECType>(IECType{ "int" }) };

        Type::Sptr Jtyp{ make_shared<JavaType>(JavaType{ "int" }) };

        IECVariable IECVar{ "asdf" };
        IECVar.SetType(Itype);

        JavaVariable JavaVar{ "jklm" };
        JavaVar.SetType(Jtyp);

        cout << "\n \n**** Test IEC Var Getter ****\n \n ";
        TestOK = TestOK && TestVariable(&IECVar, "asdf", Itype);

        cout << "\n \n**** Test Java Var Getter ****\n \n ";
        TestOK = TestOK && TestVariable(&JavaVar, "jklm", Jtyp);

        cout << "\n \n**** Test IEC Type Getter ****\n \n ";
        TestOK = TestOK && TestType(Itype);

        cout << "\n \n**** Test Java Type Getter ****\n \n ";
        TestOK = TestOK && TestType(Jtyp);

        TestOK = TestOK && TestIECVar();

        TestOK = TestOK && TestJavaVar();

        TestOK = TestOK && TestIECType();

        TestOK = TestOK && TestJavaType();

        TestOK = TestOK && TestSymbolParser();

        if (WriteOutputFile) {

            // Erase previos Symbol files for test cases
            EraseFile("IECTypes.sym");
            EraseFile("IECVars.sym");
            EraseFile("JavaTypes.sym");
            EraseFile("JavaVars.sym");


            Type::Sptr Itype1{ make_shared<IECType>(IECType{ "int" }) };

            Type::Sptr Jtyp1{ make_shared<JavaType>(JavaType{ "int" }) };

            IECVariable IECVar1{ "asdf" };
            IECVar1.SetType(Itype1);

            JavaVariable JavaVar1{ "jklm" };
            JavaVar1.SetType(Jtyp1);

            output << TestStart;

            output << "\n \n**** Test IEC Var Getter ****\n \n ";
            TestOK = TestOK && TestVariable(&IECVar1, "asdf", Itype1, output);

            output << "\n \n**** Test Java Var Getter ****\n \n ";
            TestOK = TestOK && TestVariable(&JavaVar1, "jklm", Jtyp1, output);

            output << "\n \n**** Test IEC Type Getter ****\n \n ";
            TestOK = TestOK && TestType(Itype1, output);

            output << "\n \n**** Test Java Type Getter ****\n \n ";
            TestOK = TestOK && TestType(Jtyp1, output);

            TestOK = TestOK && TestIECVar(output);

            TestOK = TestOK && TestJavaVar(output);

            TestOK = TestOK && TestIECType(output);

            TestOK = TestOK && TestJavaType(output);

            TestOK = TestOK && TestSymbolParser(output);

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
}

bool TestVariable(Variable* var, const string& name, Type::Sptr typ, ostream& ost)
{
    assert(ost.good());
    assert(var != nullptr);
    assert(typ != nullptr);

    ost << TestStart;

    bool TestOK = true;
    string error_msg;

    try {
    
        TestOK = TestOK && check_dump(ost, "Test Variable Get Name", name, var->GetName());
        TestOK = TestOK && check_dump(ost, "Test Variable Get Type", typ->GetName(), var->GetTypeName());

        const string var_name = "uint_fast_256_t";

        var->SetName(var_name);

        TestOK = TestOK && check_dump(ost, "Test Variable Set Name", var_name, var->GetName());

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

    TestOK = TestOK && check_dump(ost, "Check for Exception in Testcase", true, error_msg.empty());
    error_msg.clear();


    try {
        var->SetName("");
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

    TestOK = TestOK && check_dump(ost, "Test Exception in Set Name", Variable::ERROR_EMPTY_STRING, error_msg);
    error_msg.clear();

    try {
        var->SetType(nullptr);
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

    TestOK = TestOK && check_dump(ost, "Test Exception in Set Type with nullptr", Variable::ERROR_NULLPTR, error_msg);
    error_msg.clear();


    try {
        TestOK = TestOK && check_dump(ost, "Test Variable Get Type after set with nullptr", typ->GetName(), var->GetTypeName());

        typ->SetName("uint_fast512_t");
        var->SetType(typ);

        TestOK = TestOK && check_dump(ost, "Test Variable Get Type after set", typ->GetName(), var->GetTypeName());

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

    TestOK = TestOK && check_dump(ost, "Test for Exception in TestCase", true, error_msg.empty());
    error_msg.clear();

    ost << TestEnd;

    return TestOK;
}

bool TestType(Type::Sptr typ, ostream& ost)
{
    assert(ost.good());
    assert(typ != nullptr);

    ost << TestStart;

    bool TestOK = true;
    string error_msg;

    try {
        typ->SetName("unit_1024_t");
        TestOK = TestOK && check_dump(ost, "Test Type Get Name after Set", static_cast<string>("unit_1024_t"), typ->GetName());
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

    TestOK = TestOK && check_dump(ost, "Test Exception in Set Type", true , error_msg.empty());
    error_msg.clear();



    try {
        typ->SetName("");
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

    TestOK = TestOK && check_dump(ost, "Test Exception in Set Type", Type::ERROR_EMPTY_STRING, error_msg);
    error_msg.clear();

    ost << TestEnd;

    return TestOK;
}

bool TestIECVar(ostream& ost)
{
    assert(ost.good());

    ost << TestStart;


    bool TestOK = true;
    string error_msg;

    try {

        IECVariable var;

        const string LineToDecode = "VAR mCont : SpeedController;\n";
        TestOK == TestOK && check_dump(ost,"Test Load Type Name IEC Var",static_cast<string>("mCont"), var.LoadTypeName(LineToDecode));
        TestOK == TestOK && check_dump(ost,"Test Load Var Name IEC Var",static_cast<string>("SpeedController"), var.LoadVarName(LineToDecode));

        const string InvLineToDecode = "1VAR mCont : SpeedController;";
        TestOK == TestOK && check_dump(ost,"Test Load Type Name IEC Var invalid Format",static_cast<string>(""), var.LoadTypeName(InvLineToDecode));
        TestOK == TestOK && check_dump(ost,"Test Load Var Name IEC Var invalid Format",static_cast<string>(""), var.LoadVarName(InvLineToDecode));

        const string Inv2LineToDecode = "VAR mCont : SpeedController";
        TestOK == TestOK && check_dump(ost,"Test Load Type Name IEC Var invalid Format",static_cast<string>("mCont"), var.LoadTypeName(Inv2LineToDecode));
        TestOK == TestOK && check_dump(ost,"Test Load Var Name IEC Var invalid Format",static_cast<string>(""), var.LoadVarName(Inv2LineToDecode));
    
        const string Inv3LineToDecode = "Var mCont : SpeedController;";
        TestOK == TestOK && check_dump(ost,"Test Load Type Name IEC Var invalid Format",static_cast<string>(""), var.LoadTypeName(Inv3LineToDecode));
        TestOK == TestOK && check_dump(ost,"Test Load Var Name IEC Var invalid Format",static_cast<string>(""), var.LoadVarName(Inv3LineToDecode));
    
        const string Inv4LineToDecode = "VAR mCont : 12343;";
        TestOK == TestOK && check_dump(ost,"Test Load Type Name IEC Var invalid Format",static_cast<string>("mCont"), var.LoadTypeName(Inv4LineToDecode));
        TestOK == TestOK && check_dump(ost,"Test Load Var Name IEC Var invalid Format",static_cast<string>(""), var.LoadVarName(Inv4LineToDecode));
    
        const string Inv5LineToDecode = "VAR 123 : a12343;";
        TestOK == TestOK && check_dump(ost,"Test Load Type Name IEC Var invalid Format",static_cast<string>(""), var.LoadTypeName(Inv5LineToDecode));
        TestOK == TestOK && check_dump(ost,"Test Load Var Name IEC Var invalid Format",static_cast<string>(""), var.LoadVarName(Inv5LineToDecode));
    
        const string Inv6LineToDecode = "";
        TestOK == TestOK && check_dump(ost,"Test Load Type Name IEC Var invalid Format",static_cast<string>(""), var.LoadTypeName(Inv6LineToDecode));
        TestOK == TestOK && check_dump(ost,"Test Load Var Name IEC Var invalid Format",static_cast<string>(""), var.LoadVarName(Inv6LineToDecode));

        Type::Sptr IECTyp = make_shared<IECType>( IECType{} );
        var.SetName(var.LoadVarName(LineToDecode));
        IECTyp->SetName(var.LoadTypeName(LineToDecode));
        var.SetType(IECTyp);

        TestOK == TestOK && check_dump(ost, "Test Save LineFormat IEC Variable", LineToDecode, var.GetSaveLine());

        IECVariable IVar;

        TestOK == TestOK && check_dump(ost, "Test Save LineFormat IEC Variable", static_cast<string>(""), IVar.GetSaveLine());

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

    TestOK = TestOK && check_dump(ost, "Test for Exception in TestCase", true, error_msg.empty());
    error_msg.clear();

    ost << TestEnd;

    return TestOK;
}

bool TestJavaVar(ostream& ost)
{
    assert(ost.good());

    ost << TestStart;


    bool TestOK = true;
    string error_msg;

    try {

        JavaVariable var;

        const string LineToDecode = "mCont mBut;\n";
        TestOK == TestOK && check_dump(ost,"Test Load Type Name Java Var",static_cast<string>("mCont"), var.LoadTypeName(LineToDecode));
        TestOK == TestOK && check_dump(ost,"Test Load Var Name Java Var",static_cast<string>("mBut"), var.LoadVarName(LineToDecode));

        const string InvLineToDecode = "1mCont mBut;";
        TestOK == TestOK && check_dump(ost,"Test Load Type Name Java Var invalid Format",static_cast<string>(""), var.LoadTypeName(InvLineToDecode));
        TestOK == TestOK && check_dump(ost,"Test Load Var Name Java Var invalid Format",static_cast<string>(""), var.LoadVarName(InvLineToDecode));

        const string Inv2LineToDecode = "mCont ;mBut;";
        TestOK == TestOK && check_dump(ost,"Test Load Type Name Java Var invalid Format",static_cast<string>("mCont"), var.LoadTypeName(Inv2LineToDecode));
        TestOK == TestOK && check_dump(ost,"Test Load Var Name Java Var invalid Format",static_cast<string>(""), var.LoadVarName(Inv2LineToDecode));
    
        const string Inv3LineToDecode = "2mCont mBut;";
        TestOK == TestOK && check_dump(ost,"Test Load Type Name Java Var invalid Format",static_cast<string>(""), var.LoadTypeName(Inv3LineToDecode));
        TestOK == TestOK && check_dump(ost,"Test Load Var Name Java Var invalid Format",static_cast<string>(""), var.LoadVarName(Inv3LineToDecode));
    
        const string Inv4LineToDecode = "mCont 123;";
        TestOK == TestOK && check_dump(ost,"Test Load Type Name Java Var invalid Format",static_cast<string>("mCont"), var.LoadTypeName(Inv4LineToDecode));
        TestOK == TestOK && check_dump(ost,"Test Load Var Name Java Var invalid Format",static_cast<string>(""), var.LoadVarName(Inv4LineToDecode));
    
        const string Inv5LineToDecode = "123 : a12343;";
        TestOK == TestOK && check_dump(ost,"Test Load Type Name Java Var invalid Format",static_cast<string>(""), var.LoadTypeName(Inv5LineToDecode));
        TestOK == TestOK && check_dump(ost,"Test Load Var Name Java Var invalid Format",static_cast<string>(""), var.LoadVarName(Inv5LineToDecode));
    
        const string Inv6LineToDecode = "";
        TestOK == TestOK && check_dump(ost,"Test Load Type Name Java Var invalid Format",static_cast<string>(""), var.LoadTypeName(Inv6LineToDecode));
        TestOK == TestOK && check_dump(ost,"Test Load Var Name Java Var invalid Format",static_cast<string>(""), var.LoadVarName(Inv6LineToDecode));

        Type::Sptr JTyp = make_shared<JavaType>(JavaType{});
        var.SetName(var.LoadVarName(LineToDecode));
        JTyp->SetName(var.LoadTypeName(LineToDecode));
        var.SetType(JTyp);

        TestOK == TestOK && check_dump(ost, "Test Save LineFormat IEC Variable", LineToDecode, var.GetSaveLine());

        JavaVariable JVar;

        TestOK == TestOK && check_dump(ost, "Test Save LineFormat IEC Variable", static_cast<string>(""), JVar.GetSaveLine());
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

    TestOK = TestOK && check_dump(ost, "Test for Exception in TestCase", true, error_msg.empty());
    error_msg.clear();

    ost << TestEnd;

    return TestOK;
}

bool TestIECType(ostream& ost)
{
    assert(ost.good());

    ost << TestStart;


    bool TestOK = true;
    string error_msg;

    try{
        IECType typ;

        const string LineToDecode = "TYPE SpeedController\n";
        TestOK == TestOK && check_dump(ost, "Test Load Type Name IEC Type", static_cast<string>("SpeedController"), typ.LoadTypeName(LineToDecode));

        const string InvLineToDecode = "1TYPE SpeedController";
        TestOK == TestOK && check_dump(ost, "Test Load Type Name IEC Type invalid Format", static_cast<string>(""), typ.LoadTypeName(InvLineToDecode));

        const string Inv2LineToDecode = "TYPE 1SpeedController";
        TestOK == TestOK && check_dump(ost, "Test Load Type Name IEC Type invalid Format", static_cast<string>(""), typ.LoadTypeName(Inv2LineToDecode));

        const string Inv3LineToDecode = "TYPE S2peedController";
        TestOK == TestOK && check_dump(ost, "Test Load Type Name IEC Type invalid Format", static_cast<string>("S2peedController"), typ.LoadTypeName(Inv3LineToDecode));

        const string Inv4LineToDecode = "TYPE SpeedController;";
        TestOK == TestOK && check_dump(ost, "Test Load Type Name IEC Type invalid Format", static_cast<string>(""), typ.LoadTypeName(Inv4LineToDecode));

        const string Inv6LineToDecode = "";
        TestOK == TestOK && check_dump(ost, "Test Load Type Name IEC Type invalid Format", static_cast<string>(""), typ.LoadTypeName(Inv6LineToDecode));

        typ.SetName(typ.LoadTypeName(LineToDecode));

        TestOK == TestOK && check_dump(ost, "Test Save LineFormat IEC Type", LineToDecode, typ.GetSaveLine());

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

    TestOK = TestOK && check_dump(ost, "Test for Exception in TestCase", true, error_msg.empty());
    error_msg.clear();

    ost << TestEnd;

    return TestOK;
}

bool TestJavaType(ostream& ost)
{
    assert(ost.good());

    ost << TestStart;


    bool TestOK = true;
    string error_msg;

    try{

        JavaType typ;

        const string LineToDecode = "class SpeedController\n";
        TestOK == TestOK && check_dump(ost, "Test Load Type Name Java Type", static_cast<string>("SpeedController"), typ.LoadTypeName(LineToDecode));

        const string InvLineToDecode = "1class SpeedController";
        TestOK == TestOK && check_dump(ost, "Test Load Type Name Java Type invalid Format", static_cast<string>(""), typ.LoadTypeName(InvLineToDecode));

        const string Inv2LineToDecode = "class 1SpeedController";
        TestOK == TestOK && check_dump(ost, "Test Load Type Name Java Type invalid Format", static_cast<string>(""), typ.LoadTypeName(Inv2LineToDecode));

        const string Inv3LineToDecode = "class S2peedController";
        TestOK == TestOK && check_dump(ost, "Test Load Type Name Java Type invalid Format", static_cast<string>("S2peedController"), typ.LoadTypeName(Inv3LineToDecode));

        const string Inv4LineToDecode = "class SpeedController;";
        TestOK == TestOK && check_dump(ost, "Test Load Type Name Java Type invalid Format", static_cast<string>(""), typ.LoadTypeName(Inv4LineToDecode));

        const string Inv6LineToDecode = "";
        TestOK == TestOK && check_dump(ost, "Test Load Type Name Java Type invalid Format", static_cast<string>(""), typ.LoadTypeName(Inv6LineToDecode));

        typ.SetName(typ.LoadTypeName(LineToDecode));

        TestOK == TestOK && check_dump(ost, "Test Save LineFormat Java Type", LineToDecode, typ.GetSaveLine());

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

    TestOK = TestOK && check_dump(ost, "Test for Exception in TestCase", true, error_msg.empty());
    error_msg.clear();

    ost << TestEnd;

    return TestOK;
}


