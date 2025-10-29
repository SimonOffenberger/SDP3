#ifndef CLIENT_HPP
#define CLIENT_HPP

#include "Object.hpp"
#include "IPlayer.hpp"
#include <iostream>

class Client : public Object
{
public:
	bool Test_IPlayerVolumeCTRL(std::ostream& ost, IPlayer& player) const;
	bool Test_IPlayerPlay(std::ostream& ost, IPlayer& player) const;
};

#endif // !CLIENT_HPP