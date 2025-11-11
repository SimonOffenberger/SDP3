#include "IECVariable.hpp"
#include "JavaVariable.hpp"
#include "IECType.hpp"
#include "JavaType.hpp"
#include "SymbolParser.hpp"
#include "JavaSymbolFactory.hpp"
#include "IECSymbolFactory.hpp"
#include "Test.hpp"
#include "vld.h"
#include <fstream>
#include <iostream>
#include <cassert>

using namespace std;

#define WriteOutputFile ON

static bool TestVariableGetter(Variable* var, const string & name, Type::Sptr typ, ostream & ost = cout);
static bool TestIECVar(ostream& ost = cout);
static bool TestJavaVar(ostream& ost = cout);


int main()
{
    IECVariable Var;

    cout << "Typename : " << Var.LoadTypeName("VAR mCont : A21234;") << endl;
    cout << "Varname : " << Var.LoadVarName("VAR mCont : A21234;") << endl;

    JavaVariable javaVar;
    cout << "Typename : " << javaVar.LoadTypeName("container mCont;") << endl;
    cout << "Varname : " << javaVar.LoadVarName("container mCont;") << endl;

    JavaType javaType;
    cout << "Typename : " << javaType.LoadTypeName("class Button") << endl;

    IECType iecType;
    cout << "Typename : " << iecType.LoadTypeName("TYPE SpeedController") << endl;

    SymbolParser parser{JavaSymbolFactory::GetInstance()};

    parser.AddType("Button");
    parser.AddType("Hugo");
    parser.AddType("Window");
    parser.AddVariable("mBut", "Button");

    parser.SetFactory(IECSymbolFactory::GetInstance());

    parser.AddType("Button1");
    parser.AddType("Hugo1");
    parser.AddType("Window2");
    parser.AddVariable("mBut1", "Button1");

    parser.SetFactory(JavaSymbolFactory::GetInstance());

    bool TestOK = true;

    cout << TestStart;

    Type::Sptr Itype{make_shared<IECType>( IECType{ "int" } )};

    Type::Sptr Jtyp{make_shared<JavaType>(JavaType{ "int" } )};


    IECVariable IECVar{ "asdf" };
    IECVar.SetType(Itype);

    JavaVariable JavaVar{ "jklm" };
    JavaVar.SetType(Jtyp);

    cout << "\n \n**** Test IEC Var Getter ****\n \n ";
    TestOK = TestOK && TestVariableGetter(&IECVar, "asdf", Itype);

    cout << "\n \n**** Test Java Var Getter ****\n \n ";
    TestOK = TestOK && TestVariableGetter(&JavaVar, "jklm",Jtyp);

    TestOK = TestOK && TestIECVar();

    TestOK = TestOK && TestJavaVar();


    if (WriteOutputFile) {
        ofstream output{ "output.txt" };

        output << TestStart;

        output << "\n \n**** Test IEC Var Getter ****\n \n ";
        TestOK = TestOK && TestVariableGetter(&IECVar, "asdf", Itype,output);

        output << "\n \n**** Test Java Var Getter ****\n \n ";
        TestOK = TestOK && TestVariableGetter(&JavaVar, "jklm", Jtyp, output);

        TestOK = TestOK && TestIECVar(output);

        TestOK = TestOK && TestJavaVar(output);
    }

    return 0;
}

bool TestVariableGetter(Variable* var, const string& name, Type::Sptr typ, ostream& ost)
{
    assert(ost.good());
    assert(var != nullptr);
    assert(typ != nullptr);

    ost << TestStart;

    bool TestOK = true;
    string error_msg;
    
    TestOK = TestOK && check_dump(ost, "Test Variable Get Name", name, var->GetName());
    TestOK = TestOK && check_dump(ost, "Test Variable Get Type", typ->GetType(), var->GetType());


    try {

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
        TestOK = TestOK && check_dump(ost, "Test Variable Get Type after set with nullptr", typ->GetType(), var->GetType());

        typ->SetType("uint_fast512_t");
        var->SetType(typ);

        TestOK = TestOK && check_dump(ost, "Test Variable Get Type after set", typ->GetType(), var->GetType());

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

bool TestIECVar(ostream& ost)
{
    assert(ost.good());

    ost << TestStart;


    bool TestOK = true;
    string error_msg;

    IECVariable var;

    const string LineToDecode = "VAR mCont : SpeedController;";
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
    IECTyp->SetType(var.LoadTypeName(LineToDecode));
    var.SetType(IECTyp);

    TestOK == TestOK && check_dump(ost, "Test Save LineFormat IEC Variable", LineToDecode, var.GetSaveLine());

    IECVariable IVar;

    TestOK == TestOK && check_dump(ost, "Test Save LineFormat IEC Variable", static_cast<string>(""), IVar.GetSaveLine());

    ost << TestEnd;

    return TestOK;
}

bool TestJavaVar(ostream& ost)
{
    assert(ost.good());

    ost << TestStart;


    bool TestOK = true;
    string error_msg;

    JavaVariable var;

    const string LineToDecode = "mCont mBut";
    TestOK == TestOK && check_dump(ost,"Test Load Type Name Java Var",static_cast<string>("mCont"), var.LoadTypeName(LineToDecode));
    TestOK == TestOK && check_dump(ost,"Test Load Var Name Java Var",static_cast<string>("mBut"), var.LoadVarName(LineToDecode));

    const string InvLineToDecode = "1mCont mBut";
    TestOK == TestOK && check_dump(ost,"Test Load Type Name Java Var invalid Format",static_cast<string>(""), var.LoadTypeName(InvLineToDecode));
    TestOK == TestOK && check_dump(ost,"Test Load Var Name Java Var invalid Format",static_cast<string>(""), var.LoadVarName(InvLineToDecode));

    const string Inv2LineToDecode = "mCont ;mBut";
    TestOK == TestOK && check_dump(ost,"Test Load Type Name Java Var invalid Format",static_cast<string>("mCont"), var.LoadTypeName(Inv2LineToDecode));
    TestOK == TestOK && check_dump(ost,"Test Load Var Name Java Var invalid Format",static_cast<string>(""), var.LoadVarName(Inv2LineToDecode));
    
    const string Inv3LineToDecode = "2mCont mBut";
    TestOK == TestOK && check_dump(ost,"Test Load Type Name Java Var invalid Format",static_cast<string>(""), var.LoadTypeName(Inv3LineToDecode));
    TestOK == TestOK && check_dump(ost,"Test Load Var Name Java Var invalid Format",static_cast<string>(""), var.LoadVarName(Inv3LineToDecode));
    
    const string Inv4LineToDecode = "mCont 123";
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
    JTyp->SetType(var.LoadTypeName(LineToDecode));
    var.SetType(JTyp);

    TestOK == TestOK && check_dump(ost, "Test Save LineFormat IEC Variable", LineToDecode, var.GetSaveLine());

    JavaVariable JVar;

    TestOK == TestOK && check_dump(ost, "Test Save LineFormat IEC Variable", static_cast<string>(""), JVar.GetSaveLine());

    ost << TestEnd;

    return TestOK;
}
