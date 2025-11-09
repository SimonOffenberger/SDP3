#include "IECVariable.hpp"
#include "JavaVariable.hpp"
#include <iostream>

using namespace std;

int main()
{
    IECVariable Var;

    cout << "Typename : " << Var.LoadTypeName("VAR mCont : A21234;") << endl;
    cout << "Varname : " << Var.LoadVarName("VAR mCont : A21234;") << endl;

    JavaVariable javaVar;
    cout << "Typename : " << javaVar.LoadTypeName("container mCont;") << endl;
    cout << "Varname : " << javaVar.LoadVarName("container mCont;") << endl;

    return 0;
}