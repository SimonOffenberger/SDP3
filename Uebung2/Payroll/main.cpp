#include "Company.hpp"
#include <iostream>

using namespace std;

int main(void){
	Company comp{"Offenberger Devices"};

	comp.PrintDataSheet(cout);
}
