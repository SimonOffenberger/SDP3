/*****************************************************************//**
 * \file   MusicPlayerAdapter.cpp
 * \brief  Adapter for a Musicplayer to comply with Interface IPlayer
 * 
 * 
 * \author Simon
 * \date   November 2025
 *********************************************************************/

#include "MusicPlayerAdapter.hpp"
#include <iostream>

void MusicPlayerAdapter::Play()
{
    m_player.Start();
}

void MusicPlayerAdapter::VollInc()
{
    m_player.IncreaseVol(1);
}

void MusicPlayerAdapter::VollDec()
{
    m_player.DecreaseVol(1);
}

void MusicPlayerAdapter::Stop()
{
    m_player.Stop();
}

void MusicPlayerAdapter::Next()
{
    m_player.SwitchNext();
}

void MusicPlayerAdapter::Prev()
{
    // The MusicPlayer does not provide a prevSong 
    // function - so we need to skip forward until
    // we hit the previus song.
    size_t skipSongs = m_player.GetCount() - 1;
    
    for (int i = 0; i < skipSongs; i++)
        m_player.SwitchNext();
}

void MusicPlayerAdapter::Select(std::string const& name)
{
    if (!m_player.Find(name)) std::cout << "song: " << name << " not found!" << std::endl;
}
