#include "Video.hpp"
#include "VideoPlayer.hpp"
#include "VideoPlayerAdapter.hpp"
#include "MusicPlayer.hpp"
#include "MusicPlayerAdapter.hpp"
#include "Client.hpp"
#include <iostream>
#include <fstream>
#include <cassert>
#include "Test.hpp"

using namespace std;

#define WRITE_OUTPUT true

static bool TestSong(ostream& ost);
static bool TestVideo(ostream& ost);

int main(void){

	ofstream testoutput;
	bool TestOK = true;

	try {

		if (WRITE_OUTPUT == true) {
			testoutput.open("TestOutput.txt");
		}

		VideoPlayer VPlayer;

		VPlayer.Add("Harry Potter1", 160, EVideoFormat::AVI);
		VPlayer.Add("Harry Potter2", 160, EVideoFormat::AVI);
		VPlayer.Add("Harry Potter3", 160, EVideoFormat::AVI);
		VPlayer.Add("Harry Potter4", 160, EVideoFormat::AVI);
		VPlayer.Add("Harry Potter5", 160, EVideoFormat::AVI);
		VPlayer.Add("Harry Potter6", 160, EVideoFormat::AVI);

		VideoPlayerAdapter VidAdapter{ VPlayer };
	
		Client client;

		cout << "Test VideoPlayer Adapter in Client" << endl;
		TestOK = TestOK && client.Test_IPlayerVolumeCTRL(cout,VidAdapter,VideoPlayer::MAX_VOLUME,VideoPlayer::DEFAULT_VOLUME);
		TestOK = TestOK && client.Test_IPlayerPlay(cout,VidAdapter);
		
		if (WRITE_OUTPUT) {
			testoutput << "Test VideoPlayer Adapter in Client" << endl;
			TestOK = TestOK && client.Test_IPlayerVolumeCTRL(testoutput, VidAdapter, VideoPlayer::MAX_VOLUME, VideoPlayer::DEFAULT_VOLUME);
			TestOK = TestOK && client.Test_IPlayerPlay(testoutput, VidAdapter);
		}
		VideoPlayer EmptyPlayer;
		VideoPlayerAdapter EmptyAdapter { EmptyPlayer };

		TestOK = TestOK && client.Test_IPlayerEmptyPlay(cout, EmptyAdapter);

		if (WRITE_OUTPUT) TestOK = TestOK && client.Test_IPlayerEmptyPlay(testoutput, EmptyAdapter);

		MusicPlayer MPlayer;


		MPlayer.Add("Harry Potter1", 160);
		MPlayer.Add("Harry Potter2", 160);
		MPlayer.Add("Harry Potter3", 160);
		MPlayer.Add("Harry Potter4", 160);
		MPlayer.Add("Harry Potter5", 160);
		MPlayer.Add("Harry Potter6", 160);

		MusicPlayerAdapter MusAdapter{ MPlayer };
	
		cout << "Test MusicPlayer Adapter in Client" << endl;
		TestOK = TestOK && client.Test_IPlayerVolumeCTRL(cout, MusAdapter,MusicPlayer::MAX_VOLUME,MusicPlayer::DEFAULT_VOLUME);
		TestOK = TestOK && client.Test_IPlayerPlay(cout, MusAdapter);
		
		if (WRITE_OUTPUT) {
			testoutput << "Test MusicPlayer Adapter in Client" << endl;
			TestOK = TestOK && client.Test_IPlayerVolumeCTRL(testoutput, MusAdapter, MusicPlayer::MAX_VOLUME, MusicPlayer::DEFAULT_VOLUME);
			TestOK = TestOK && client.Test_IPlayerPlay(testoutput, MusAdapter);
		}

		TestOK = TestOK && TestSong(cout);
		if (WRITE_OUTPUT) TestOK = TestOK && TestSong(testoutput);

		TestOK = TestOK && TestVideo(cout);
		if (WRITE_OUTPUT) TestOK = TestOK && TestVideo(testoutput);

		if (WRITE_OUTPUT) {
			if (TestOK) TestCaseOK(testoutput);
			else TestCaseFail(testoutput);

			testoutput.close();
		}

		if (TestOK) TestCaseOK(cout);
		else TestCaseFail(cout);

	}
	catch (const string& err) {
		cerr << err;
	}
	catch (bad_alloc const& error) {
		cerr << error.what();
	}
	catch (const exception& err) {
		cerr << err.what();
	}
	catch (...) {
		cerr << "Unhandelt Exception";
	}

	if (testoutput.is_open()) testoutput.close();

	return 0;
}

bool TestSong(ostream& ost)
{
	assert(ost.good());

	TestStart(ost);

	bool TestOK = true;
	string error_msg = "";

	try {

		Song HelloWorld("Hello World", 123);

		TestOK = TestOK && check_dump(ost,"Test Song Getter Duration", static_cast<size_t>(123), HelloWorld.GetDuration());

		TestOK = TestOK && check_dump(ost,"Test Song Getter Name",static_cast<string>( "Hello World"), HelloWorld.GetTitle());

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

	TestEnd(ost);
	return TestOK;
}

bool TestVideo(ostream& ost)
{
	assert(ost.good());

	TestStart(ost);

	bool TestOK = true;
	string error_msg = "";

	try {

		Video HelloWorld("Hello World", 123,EVideoFormat::AVI);

		TestOK = TestOK && check_dump(ost,"Test Song Getter Duration", static_cast<size_t>(123), HelloWorld.GetDurration());

		TestOK = TestOK && check_dump(ost,"Test Song Getter Name",static_cast<string>( "Hello World"), HelloWorld.GetTitle());

		TestOK = TestOK && check_dump(ost,"Test Song Getter Format", static_cast<string>("AVI-Format"), HelloWorld.GetFormatID());
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

	TestEnd(ost);
	return TestOK;
}
