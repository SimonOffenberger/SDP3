#include "Client.hpp"
#include "Test.hpp"
#include <sstream>
#include <algorithm>

using namespace std;

bool Client::Test_IPlayerVolumeCTRL(std::ostream& ost, IPlayer& player) const
{
	if (!ost.good()) throw Client::ERROR_BAD_OSTREAM;

	TestStart(ost);

	bool TestOK = true;
	string error_msg = "";

	try {

		stringstream result;

		player.VollInc(result);

		check_dump(ost, "Test Volume Inc", true, result.str().find("9")!=std::string::npos);

		result.clear();

		player.VollDec(result);

		check_dump(ost, "Test Volume Dec", true, result.str().find("8")!=std::string::npos);

		for (int i = 0;i < 200; i++) player.VollDec(result);

		result.clear();

		player.VollDec(result);

		check_dump(ost, "Test Lower Bound Volume 0", true, result.str().find("0") != std::string::npos);

		for (int i = 0;i < 200; i++) player.VollInc(result);

		result.clear();

		player.VollInc(result);

		check_dump(ost, "Test Upper Bound Volume 100", true, result.str().find("100") != std::string::npos);
	}
	catch (const string& err) {
		error_msg = err;
		TestOK = false;
	}
	catch (bad_alloc const& error) {
		error_msg = error.what();
		TestOK = false;
	}
	catch (const exception& err) {
		error_msg = err.what();
		TestOK = false;
	}
	catch (...) {
		error_msg = "Unhandelt Exception";
		TestOK = false;
	}

	check_dump(ost, "Test for Exceotion in Test Case", true,error_msg.empty());

	TestEnd(ost);

	if (ost.fail()) throw Client::ERROR_FAIL_WRITE;

	return TestOK;
}

bool Client::Test_IPlayerPlay(std::ostream& ost, IPlayer& player) const
{
	if (!ost.good()) throw Client::ERROR_BAD_OSTREAM;

	TestStart(ost);

	bool TestOK = true;
	string error_msg = "";

	try {

		stringstream result;

		player.Play(result);

		check_dump(ost, "Test Play Contains Name", true, result.str().find("Harry Potter1") != std::string::npos);

	}
	catch (const string& err) {
		error_msg = err;
		TestOK = false;
	}
	catch (bad_alloc const& error) {
		error_msg = error.what();
		TestOK = false;
	}
	catch (const exception& err) {
		error_msg = err.what();
		TestOK = false;
	}
	catch (...) {
		error_msg = "Unhandelt Exception";
		TestOK = false;
	}

	check_dump(ost, "Test for Exceotion in Test Case", true, error_msg.empty());

	TestEnd(ost);

	if (ost.fail()) throw Client::ERROR_FAIL_WRITE;

	return TestOK;
}
