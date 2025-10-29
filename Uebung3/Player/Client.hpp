#ifndef CLIENT_HPP
#define CLIENT_HPP

#include "Object.hpp"
#include "IPlayer.hpp"

class Client : public Object
{
public:
	bool Test_IPlayerGetter(IPlayer & player) const;

};

#endif // !CLIENT_HPP