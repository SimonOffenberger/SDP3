#include "Video.hpp"
#include "VideoPlayer.hpp"
#include "VideoPlayerAdapter.hpp"
#include "Client.hpp"
#include <iostream>

using namespace std;

int main(void){

	VideoPlayer VPlayer;


	VPlayer.Add("Harry Potter1", 160, EVideoFormat::AVI);
	VPlayer.Add("Harry Potter2", 160, EVideoFormat::AVI);
	VPlayer.Add("Harry Potter3", 160, EVideoFormat::AVI);
	VPlayer.Add("Harry Potter4", 160, EVideoFormat::AVI);
	VPlayer.Add("Harry Potter5", 160, EVideoFormat::AVI);
	VPlayer.Add("Harry Potter6", 160, EVideoFormat::AVI);

	VideoPlayerAdapter VidAdapter{ VPlayer };
	
	Client client;

	client.Test_IPlayerVolumeCTRL(cout,VidAdapter);
	client.Test_IPlayerPlay(cout,VidAdapter);


	return 0;
}
