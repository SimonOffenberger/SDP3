#include "Company.hpp"
#include "Employee.hpp"
#include "HourlyWorker.hpp"
#include "vld.h"
#include "Client.hpp"
#include "Test.hpp"
#include "ComissionWorker.hpp"
#include "HourlyWorker.hpp"
#include "Boss.hpp"
#include "PieceWorker.hpp"
#include <iostream>
#include <fstream>

using namespace std;
using namespace std::chrono;

#define WRITE_OUTPUT false

int main(void){
	bool TestOK = true;
	ofstream testoutput;

	if (WRITE_OUTPUT == true) {
		testoutput.open("output.txt");
	}

	 Company comp{"Offenberger Devices"};	
	 Client TestClient;


	 TestOK = TestOK && TestClient.TestCompanyGetter(cout, comp);
	 if(WRITE_OUTPUT) TestOK = TestOK && TestClient.TestCompanyGetter(testoutput, comp);

	 // Copy Ctor Call !
	 Company compCopy = comp; 

	 TestOK = TestOK && TestClient.TestCompanyCopyCTOR(cout, comp, compCopy);
	 if (WRITE_OUTPUT) TestOK = TestOK && TestClient.TestCompanyCopyCTOR(testoutput, comp, compCopy);	 
	 
	 // Test Assign Operator
	 Company compAss{"Assign Company"};
	 compAss = comp;

	 TestOK = TestOK && TestClient.TestCompanyAssignOp(cout, comp, compAss);
	 if (WRITE_OUTPUT) TestOK = TestOK && TestClient.TestCompanyAssignOp(testoutput, comp, compAss);


	 TestOK = TestOK && TestClient.TestCompanyPrint(cout, comp);
	 if (WRITE_OUTPUT) TestOK = TestOK && TestClient.TestCompanyPrint(testoutput, comp);

	 Company emptyComp{"empty"};

	 TestOK = TestOK && TestClient.TestEmptyCompanyGetter(cout, emptyComp);
	 if (WRITE_OUTPUT) TestOK = TestOK && TestClient.TestEmptyCompanyGetter(testoutput, emptyComp);

	 // Test Boss
	 TestOK = TestOK && TestClient.TestEmployeeBoss(cout);
	 if (WRITE_OUTPUT) TestOK = TestOK && TestClient.TestEmployeeBoss(testoutput);

	 // Test Hourly Worker
	 TestOK = TestOK && TestClient.TestEmployeeHourlyWorker(cout);
	 if (WRITE_OUTPUT) TestOK = TestOK && TestClient.TestEmployeeHourlyWorker(testoutput);

	 // Test Piece Worker
	 TestOK = TestOK && TestClient.TestEmployeePieceWorker(cout);
	 if (WRITE_OUTPUT) TestOK = TestOK && TestClient.TestEmployeePieceWorker(testoutput);

	 // Test Comission Worker
	 TestOK = TestOK && TestClient.TestEmployeeComissionWorker(cout);
	 if (WRITE_OUTPUT) TestOK = TestOK && TestClient.TestEmployeeComissionWorker(testoutput);

	 if (WRITE_OUTPUT){
		 if (TestOK) TestCaseOK(testoutput);
		 else TestCaseFail(testoutput);

		 testoutput.close();
	 }

	 if (TestOK) TestCaseOK(cout);
	 else TestCaseFail(cout);

}
