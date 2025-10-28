#include "Video.hpp"
#include "VideoPlayer.hpp"
#include "VideoPlayerAdapter.hpp"
#include "AVI.hpp"
#include "MKV.hpp"
#include "WMV.hpp"
#include <iostream>

int main(void){

	VideoPlayer Player;
	
	Player.Add("Harry Potter1", 160, new AVI);
	Player.Add("Harry Potter2", 160, new AVI);
	Player.Add("Harry Potter3", 160, new AVI);
	Player.Add("Harry Potter4", 160, new AVI);

	VideoPlayerAdapter VidAdapter{ Player };

	VidAdapter.Play();


	return 0;
}
