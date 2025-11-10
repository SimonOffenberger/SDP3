#include "IECVariable.hpp"
#include "JavaVariable.hpp"
#include "IECType.hpp"
#include "JavaType.hpp"
#include "SymbolParser.hpp"
#include "JavaSymbolFactory.hpp"
#include "Test.hpp"
#include "vld.h"
#include <fstream>
#include <iostream>
#include <cassert>

using namespace std;

#define WriteOutputFile ON

static bool TestVariableGetter(Variable* var, const string & name, Type::Sptr typ, ostream & ost = cout);
static bool TestIECVar(ostream& ost = cout);


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


    if (WriteOutputFile) {
        ofstream output{ "output.txt" };

        output << TestStart;

        output << "\n \n**** Test IEC Var Getter ****\n \n ";
        TestOK = TestOK && TestVariableGetter(&IECVar, "asdf", Itype,output);

        output << "\n \n**** Test Java Var Getter ****\n \n ";
        TestOK = TestOK && TestVariableGetter(&JavaVar, "jklm", Jtyp, output);

        TestOK = TestOK && TestIECVar(output);
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

    ost << TestEnd;

    return TestOK;
}
