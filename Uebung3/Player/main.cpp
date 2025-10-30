#include "Video.hpp"
#include "VideoPlayer.hpp"
#include "VideoPlayerAdapter.hpp"
#include "MusicPlayer.hpp"
#include "MusicPlayerAdapter.hpp"
#include "Client.hpp"
#include <iostream>
#include <fstream>
#include "Test.hpp"

using namespace std;

#define WRITE_OUTPUT true


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
