#include "vld.h"
#include "Video.hpp"
#include "VideoPlayer.hpp"
#include "VideoPlayerAdapter.hpp"
#include "MusicPlayer.hpp"
#include "MusicPlayerAdapter.hpp"
#include "Client.hpp"
#include <iostream>
#include <fstream>
#include <cassert>
#include <sstream>
#include "Test.hpp"

using namespace std;

#define WRITE_OUTPUT true

static bool TestSong(ostream& ost);
static bool TestVideo(ostream& ost);
static bool TestVideoPlayer(ostream& ost);
static bool TestMusicPlayer(ostream& ost);

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

		TestOK = TestOK && TestVideoPlayer(cout);
		if (WRITE_OUTPUT) TestOK = TestOK && TestVideoPlayer(testoutput);

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

bool TestVideoPlayer(ostream& ost)
{
	assert(ost.good());

	TestStart(ost);

	bool TestOK = true;
	string error_msg = "";

	try {

		Video HelloWorld("Hello World", 123, EVideoFormat::AVI);
		
		VideoPlayer VPlayer;

		VPlayer.Add("Hello World1",123,EVideoFormat::AVI);
		VPlayer.Add("Hello World2",124,EVideoFormat::MKV);
		VPlayer.Add("Hello World3",125,EVideoFormat::WMV);
		VPlayer.Add("Hello World4",126,EVideoFormat::AVI);
		VPlayer.Add("Hello World5",127,EVideoFormat::MKV);

		TestOK = TestOK && check_dump(ost, "Test Videplayer Initial Index", static_cast<size_t>(0), VPlayer.CurIndex());

		VPlayer.First();

		TestOK = TestOK && check_dump(ost, "Test Videplayer Index after First", static_cast<size_t>(0), VPlayer.CurIndex());

		VPlayer.Next();

		TestOK = TestOK && check_dump(ost, "Test Videplayer Index after Next", static_cast<size_t>(1), VPlayer.CurIndex());

		for (int i = 0; i < 100;i++) VPlayer.Next();

		TestOK = TestOK && check_dump(ost, "Test Videplayer Index Upper Bound", static_cast<size_t>(4), VPlayer.CurIndex());

		VPlayer.First();

		TestOK = TestOK && check_dump(ost, "Test Videplayer Index after First", static_cast<size_t>(0), VPlayer.CurIndex());

		TestOK = TestOK && check_dump(ost, "Test Default Volume", static_cast<size_t>(8), VPlayer.GetVolume());

		std::streambuf* coutbuf = std::cout.rdbuf();

		stringstream result;

		// cout redirect to stringstream
		std::cout.rdbuf(result.rdbuf());

		VPlayer.SetVolume(25);

		std::cout.rdbuf(coutbuf);

		TestOK = TestOK && check_dump(ost, "Test Set Volume", static_cast<size_t>(25), VPlayer.GetVolume());
		
		// cout redirect to stringstream
		std::cout.rdbuf(result.rdbuf());

		VPlayer.SetVolume(300);

		std::cout.rdbuf(coutbuf);
		
		TestOK = TestOK && check_dump(ost, "Test Set Volume Max Volume", static_cast<size_t>(VideoPlayer::MAX_VOLUME), VPlayer.GetVolume());
		
		// cout redirect to stringstream
		std::cout.rdbuf(result.rdbuf());

		VPlayer.SetVolume(0);

		std::cout.rdbuf(coutbuf);
		
		TestOK = TestOK && check_dump(ost, "Test Set Volume Min Volume", static_cast<size_t>(VideoPlayer::MIN_VOLUME), VPlayer.GetVolume());


		result.str("");
		result.clear();
		// cout redirect to stringstream
		std::cout.rdbuf(result.rdbuf());

		VPlayer.Play();

		std::cout.rdbuf(coutbuf);

		TestOK = TestOK && check_dump(ost, "Test Video Player Play", true, result.str().find(VPlayer.CurVideo()) != string::npos);
		
		result.str("");
		result.clear();
		// cout redirect to stringstream
		std::cout.rdbuf(result.rdbuf());

		VPlayer.Stop();

		std::cout.rdbuf(coutbuf);

		TestOK = TestOK && check_dump(ost, "Test Video Player Stop", true, result.str().find("stop") != string::npos);
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

	try{
		VideoPlayer VidPlayer;
		VidPlayer.Add("", 123, EVideoFormat::AVI);

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

	TestOK = TestOK && check_dump(ost, "Test Exception in Add with empty string", error_msg, VideoPlayer::ERROR_EMPTY_NAME);
	error_msg.clear();
	
	try{
		VideoPlayer VidPlayer;
		VidPlayer.Add("234", 0, EVideoFormat::AVI);

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

	TestOK = TestOK && check_dump(ost, "Test Exception in Add with empty string", error_msg, VideoPlayer::ERROR_DURATION_NULL);
	error_msg.clear();


	TestEnd(ost);
	return TestOK;
}
