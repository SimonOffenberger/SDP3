#include <iostream>
#include "MusicPlayer.hpp"


void MusicPlayer::Start(std::ostream & ost = std::cout)
{
    std::cout   
        << "playing song number " << m_currentSongIdx << ": "
        << m_songs[m_currentSongIdx].GetTitle()
        << " (" << m_songs[m_currentSongIdx].GetDuration() << ")\n";
}

void MusicPlayer::Stop()
{
    std::cout 
        << "stop song number " << m_currentSongIdx << ": "
        << m_songs[m_currentSongIdx].GetTitle()
        << " (" << m_songs[m_currentSongIdx].GetDuration() << ")\n";
}

void MusicPlayer::SwitchNext()
{
    // increase until end then wrap around
    m_currentSongIdx = (m_currentSongIdx + 1) % m_songs.size();
}

size_t MusicPlayer::GetCurIndex()
{
    return m_currentSongIdx;
}

bool MusicPlayer::Find(std::string const& name)
{
    for (auto song : m_songs)
    {
        if (song.GetTitle() == name)
            return true;
    }
    return false;
}

size_t MusicPlayer::GetCount()
{
    return size_t();
}

void MusicPlayer::IncreaseVol(size_t vol)
{
}

void MusicPlayer::DecreaseVol(size_t vol)
{
}

void MusicPlayer::Add(std::string name, size_t dur)
{
}
