#include "Video.hpp"
#include "VideoPlayer.hpp"
#include "VideoPlayerAdapter.hpp"
#include "Client.hpp"
#include <iostream>

using namespace std;

int main(void){

	VideoPlayer Player;


	Player.Add("Harry Potter1", 160, EVideoFormat::AVI);
	Player.Add("Harry Potter2", 160, EVideoFormat::AVI);
	Player.Add("Harry Potter3", 160, EVideoFormat::AVI);
	Player.Add("Harry Potter4", 160, EVideoFormat::AVI);
	Player.Add("Harry Potter5", 160, EVideoFormat::AVI);
	Player.Add("Harry Potter6", 160, EVideoFormat::AVI);

	VideoPlayerAdapter VidAdapter{ Player };
	
	Client client;

	client.Test_IPlayerGetter(VidAdapter);


	return 0;
}
