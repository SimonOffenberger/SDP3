#include "IECVariable.hpp"
#include <iostream>

using namespace std;

int main()
{
    IECVariable Var;

    cout << "Typename : " << Var.LoadTypeName("VAR mCont : A21234;") << endl;
    cout << "Varname : " << Var.LoadVarName("VAR mCont : A21234;") << endl;

    return 0;
}