#include <iostream>
#include "MusicPlayer.hpp"

void MusicPlayer::Start()
{
    if (std::cout.bad())
        throw Object::ERROR_BAD_OSTREAM;

    if (m_songs.empty())
    {
        std::cout << "no songs in playlist!" << std::endl;
        return;
    }

    std::cout
        << "playing song number " << m_currentSongIdx << ": "
        << m_songs[m_currentSongIdx].GetTitle()
        << " (" << m_songs[m_currentSongIdx].GetDuration() << ")\n";
}

void MusicPlayer::Stop()
{
    if (std::cout.bad())
        throw Object::ERROR_BAD_OSTREAM;

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

size_t MusicPlayer::GetCurIndex() const
{
    return m_currentSongIdx;
}

bool MusicPlayer::Find(std::string const& name)
{
    for (int i =0; i<m_songs.size(); i++)
    {
        if (m_songs.at(i).GetTitle() == name) {
            m_currentSongIdx = i;
            return true;
        }
    }
    return false;
}

size_t MusicPlayer::GetCount()
{
    return m_songs.size();
}

void MusicPlayer::IncreaseVol(size_t vol)
{
    if (std::cout.bad())
        throw Object::ERROR_BAD_OSTREAM;

    m_volume += vol;
    if (m_volume > MAX_VOLUME)
        m_volume = MAX_VOLUME;

    std::cout << "volume is now -> " << m_volume << std::endl;
}

void MusicPlayer::DecreaseVol(size_t vol)
{
    if (std::cout.bad())
        throw Object::ERROR_BAD_OSTREAM;

    if (vol > m_volume)
        m_volume = MIN_VOLUME;
    else
        m_volume -= vol;

    std::cout << "volume is now -> " << m_volume << std::endl;
}

void MusicPlayer::Add(std::string const& name, size_t const dur)
{
    m_songs.emplace_back(name, dur);
}
