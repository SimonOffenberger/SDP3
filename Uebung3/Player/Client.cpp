#include "Client.hpp"


bool Client::Test_IPlayerGetter(IPlayer & player) const
{
	player.Play();

	return true;
}
