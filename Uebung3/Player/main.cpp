#include "Video.hpp"
#include "VideoPlayer.hpp"
#include "AVI.hpp"
#include "MKV.hpp"
#include "WMV.hpp"
#include <iostream>

int main(void){

	VideoPlayer Player;


	Player.Add("Hello World", 350,new AVI{});

	Player.First();
	Player.Play(std::cout);
	Player.SetVolume(500,std::cout);

	return 0;
}
