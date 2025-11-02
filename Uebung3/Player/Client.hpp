/*****************************************************************//**
 * \file   Client.hpp
 * \brief  Client Class that uses a IPlayer Interface inorder to control
 * \brief  a Musicplayer or a Videoplayer via their adapter
 * 
 * \author Simon
 * \date   November 2025
 *********************************************************************/
#ifndef CLIENT_HPP
#define CLIENT_HPP

#include "Object.hpp"
#include "IPlayer.hpp"
#include <iostream>

class Client : public Object
{
public:
	/**
	 * \brief Test Function for the Volume Control of the IPlayer interface.
	 * 
	 * \param ost Ostream 
	 * \param player Reference to the player
	 * \param MaxVolume Maximum Volume of the player
	 * \param DefaultVol Default Volume of the player
	 * \return true -> tests OK
	 * \return false -> tests failed
	 */
	bool Test_IPlayerVolumeCTRL(std::ostream& ost, IPlayer& player, const size_t& MaxVolume, const size_t& DefaultVol) const;
	
	/**
	 * \brief Test Play of the Player.
	 * 
	 * \param ost Ostream for the Testoutput
	 * \param player Refernce to player
	 * \return true -> tests OK
	 * \return false -> tests failed
	 */
	bool Test_IPlayerPlay(std::ostream& ost, IPlayer& player) const;

	/**
	 * \brief Test Play of an empty Player.
	 *
	 * \param ost Ostream for the Testoutput
	 * \param player Refernce to player
	 * \return true -> tests OK
	 * \return false -> tests failed
	 */
	bool Test_IPlayerEmptyPlay(std::ostream& ost, IPlayer& player) const;
};

#endif // !CLIENT_HPP