#include "Client.hpp"
#include "Test.hpp"
#include <sstream>
#include <algorithm>

using namespace std;

bool Client::Test_IPlayerVolumeCTRL(std::ostream& ost, IPlayer& player, const size_t & MaxVolume, const size_t & DefaultVol) const
{
	if (!ost.good()) throw Client::ERROR_BAD_OSTREAM;

	TestStart(ost);

	bool TestOK = true;
	string error_msg = "";

	try {

		stringstream result;

		std::streambuf* coutbuf = std::cout.rdbuf();

		result << DefaultVol+1;
		string DVol;

		result >> DVol;

		result.clear();
		result.str("");

		// cout redirect to stringstream
		std::cout.rdbuf(result.rdbuf());

		player.VollInc();

		std::cout.rdbuf(coutbuf);

		TestOK == TestOK && check_dump(ost, "Test Volume Inc", true, result.str().find(DVol)!=std::string::npos);

		result.clear();
		result.str("");

		result << DefaultVol;

		result >> DVol;

		result.clear();
		result.str("");

		// cout redirect to stringstream
		std::cout.rdbuf(result.rdbuf());

		player.VollDec();

		std::cout.rdbuf(coutbuf);

		TestOK == TestOK && check_dump(ost, "Test Volume Dec", true, result.str().find(DVol)!=std::string::npos);

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

		TestOK == TestOK && check_dump(ost, "Test Lower Bound Volume 0", true, result.str().find("0") != std::string::npos);

		// cout redirect to stringstream
		std::cout.rdbuf(result.rdbuf());

		for (int i = 0;i < 200; i++) player.VollInc();

		std::cout.rdbuf(coutbuf);

		result.clear();
		result.str("");

		result << MaxVolume;

		string MaxVol;

		result >> MaxVol;

		result.clear();
		result.str("");

		// cout redirect to stringstream
		std::cout.rdbuf(result.rdbuf());

		player.VollInc();

		std::cout.rdbuf(coutbuf);


		TestOK == TestOK && check_dump(ost, "Test Upper Bound Volume", true, result.str().find(MaxVol) != std::string::npos);
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

	TestOK == TestOK && check_dump(ost, "Test for Exceotion in Test Case", true,error_msg.empty());

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
		std::streambuf* coutbuf = std::cout.rdbuf();

		// cout redirect to stringstream
		std::cout.rdbuf(result.rdbuf());

		player.Play();

		std::cout.rdbuf(coutbuf);

		TestOK == TestOK && check_dump(ost, "Test Play Contains Name", true, result.str().find("Harry Potter1") != std::string::npos);

		player.Next();

		result.str("");
		result.clear();

		std::cout.rdbuf(result.rdbuf());

		player.Play();

		std::cout.rdbuf(coutbuf);

		TestOK == TestOK && check_dump(ost, "Test Next ", true, result.str().find("Harry Potter2") != std::string::npos);

		for (int i = 0; i < 4; i++) {

			player.Next();

			result.str("");
			result.clear();

			std::cout.rdbuf(result.rdbuf());

			player.Play();

			std::cout.rdbuf(coutbuf);

			TestOK == TestOK && check_dump(ost, "Test Next ", true, result.str().find("Harry Potter" + 2 + i) != std::string::npos);

		}

		player.Next();

		result.str("");
		result.clear();

		std::cout.rdbuf(result.rdbuf());

		player.Play();

		std::cout.rdbuf(coutbuf);

		TestOK == TestOK && check_dump(ost, "Test Next Wrap around", true, result.str().find("Harry Potter1") != std::string::npos);

		result.str("");
		result.clear();

		std::cout.rdbuf(result.rdbuf());

		player.Select("Harry Potter3");
		player.Play();

		std::cout.rdbuf(coutbuf);

		TestOK == TestOK && check_dump(ost, "Test Select Video by name ", true, result.str().find("Harry Potter3") != std::string::npos);
		
		result.str("");
		result.clear();

		std::cout.rdbuf(result.rdbuf());

		player.Select("Harry Potter14");
		player.Play();

		std::cout.rdbuf(coutbuf);

		TestOK == TestOK && check_dump(ost, "Test Select Video by name not found", true, result.str().find("not found!") != std::string::npos);
		
		result.str("");
		result.clear();

		std::cout.rdbuf(result.rdbuf());

		player.Select("Harry Potter3");
		player.Stop();

		std::cout.rdbuf(coutbuf);

		TestOK == TestOK && check_dump(ost, "Test Stop Player",
				   true,
			       result.str().find("stop") != std::string::npos && result.str().find("Harry Potter3") != std::string::npos);


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

	TestOK == TestOK && check_dump(ost, "Test for Exception in Test Case", true, error_msg.empty());

	TestEnd(ost);

	if (ost.fail()) throw Client::ERROR_FAIL_WRITE;

	return TestOK;
}

bool Client::Test_IPlayerEmptyPlay(std::ostream& ost, IPlayer& player) const
{
	if (!ost.good()) throw Client::ERROR_BAD_OSTREAM;

	TestStart(ost);

	bool TestOK = true;
	string error_msg = "";

	try {


		player.Play();


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

	ost << "Exception Message :" <<  error_msg << endl;
	TestOK == TestOK && check_dump(ost, "Test Exception Empty Video Collection",false , error_msg.empty());

	TestEnd(ost);

	if (ost.fail()) throw Client::ERROR_FAIL_WRITE;

	return TestOK;
}
