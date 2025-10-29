#include "Client.hpp"
#include "Test.hpp"
#include <sstream>
#include <algorithm>

using namespace std;

bool Client::Test_IPlayerVideoVolumeCTRL(std::ostream& ost, IPlayer& player) const
{
	if (!ost.good()) throw Client::ERROR_BAD_OSTREAM;

	TestStart(ost);

	bool TestOK = true;
	string error_msg = "";

	try {

		stringstream result;

		std::streambuf* coutbuf = std::cout.rdbuf();

		// cout redirect to stringstream
		std::cout.rdbuf(result.rdbuf());

		player.VollInc();

		std::cout.rdbuf(coutbuf);

		check_dump(ost, "Test Volume Inc", true, result.str().find("9")!=std::string::npos);

		result.clear();
		result.str("");

		// cout redirect to stringstream
		std::cout.rdbuf(result.rdbuf());

		player.VollDec();

		std::cout.rdbuf(coutbuf);

		check_dump(ost, "Test Volume Dec", true, result.str().find("8")!=std::string::npos);

		// cout redirect to stringstream
		std::cout.rdbuf(result.rdbuf());

		for (int i = 0;i < 200; i++) player.VollDec();

		player.VollInc();

		std::cout.rdbuf(coutbuf);

		result.clear();
		result.str("");


		// cout redirect to stringstream
		std::cout.rdbuf(result.rdbuf());

		player.VollDec();

		std::cout.rdbuf(coutbuf);

		check_dump(ost, "Test Lower Bound Volume 0", true, result.str().find("0") != std::string::npos);

		// cout redirect to stringstream
		std::cout.rdbuf(result.rdbuf());

		for (int i = 0;i < 200; i++) player.VollInc();

		std::cout.rdbuf(coutbuf);

		result.clear();
		result.str("");

		// cout redirect to stringstream
		std::cout.rdbuf(result.rdbuf());

		player.VollInc();

		std::cout.rdbuf(coutbuf);

		check_dump(ost, "Test Upper Bound Volume 50", true, result.str().find("50") != std::string::npos);
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

bool Client::Test_IPlayerVideoPlay(std::ostream& ost, IPlayer& player) const
{
	if (!ost.good()) throw Client::ERROR_BAD_OSTREAM;

	TestStart(ost);

	bool TestOK = true;
	string error_msg = "";

	try {

		stringstream result;
		std::streambuf* coutbuf = std::cout.rdbuf();

		// cout redirect to stringstream
		std::cout.rdbuf(result.rdbuf());

		player.Play();

		std::cout.rdbuf(coutbuf);

		check_dump(ost, "Test Play Contains Name", true, result.str().find("Harry Potter1") != std::string::npos);

		player.Next();

		result.str("");
		result.clear();

		std::cout.rdbuf(result.rdbuf());

		player.Play();

		std::cout.rdbuf(coutbuf);

		check_dump(ost, "Test Next ", true, result.str().find("Harry Potter2") != std::string::npos);

		for (int i = 0; i < 4; i++) {

			player.Next();

			result.str("");
			result.clear();

			std::cout.rdbuf(result.rdbuf());

			player.Play();

			std::cout.rdbuf(coutbuf);

			check_dump(ost, "Test Next ", true, result.str().find("Harry Potter" + 2 + i) != std::string::npos);

		}


		player.Next();
		player.Next();

		result.str("");
		result.clear();

		std::cout.rdbuf(result.rdbuf());

		player.Play();

		std::cout.rdbuf(coutbuf);

		check_dump(ost, "Test Next on upper Bound ", true, result.str().find("Harry Potter6") != std::string::npos);


		player.Select("Harry Potter3");
		player.Play();

		player.Select("Harry Potter14");
		player.Play();

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

	check_dump(ost, "Test for Exception in Test Case", true, error_msg.empty());

	TestEnd(ost);

	if (ost.fail()) throw Client::ERROR_FAIL_WRITE;

	return TestOK;
}
