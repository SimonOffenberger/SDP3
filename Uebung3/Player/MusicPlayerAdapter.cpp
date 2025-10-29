#include "MusicPlayerAdapter.hpp"

void MusicPlayerAdapter::Play(std::ostream& ost)
{
    m_player.Start(ost);
}

void MusicPlayerAdapter::VollInc(std::ostream& ost)
{
    m_player.IncreaseVol(1, ost);
}

void MusicPlayerAdapter::VollDec(std::ostream& ost)
{
    m_player.DecreaseVol(1, ost);
}

void MusicPlayerAdapter::Stop(std::ostream& ost)
{
    m_player.Start(ost);
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
