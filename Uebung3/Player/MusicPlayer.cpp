#include <iostream>
#include "MusicPlayer.hpp"

static const unsigned MAX_VOLUME = 100;
static const unsigned MIN_VOLUME = 0;

void MusicPlayer::Start(std::ostream & ost)
{
    if (ost.bad())
        throw Object::ERROR_BAD_OSTREAM;

    if (m_songs.empty())
    {
        ost << "no songs in playlist!" << std::endl;
        return;
    }

    ost
        << "playing song number " << m_currentSongIdx << ": "
        << m_songs[m_currentSongIdx].GetTitle()
        << " (" << m_songs[m_currentSongIdx].GetDuration() << ")\n";
}

void MusicPlayer::Stop(std::ostream& ost)
{
    if (ost.bad())
        throw Object::ERROR_BAD_OSTREAM;

    ost
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
    for (auto const& song : m_songs)
    {
        if (song.GetTitle() == name)
            return true;
    }
    return false;
}

size_t MusicPlayer::GetCount()
{
    return m_songs.size();
}

void MusicPlayer::IncreaseVol(size_t vol, std::ostream& ost)
{
    if (ost.bad())
        throw Object::ERROR_BAD_OSTREAM;

    m_volume += vol;
    if (m_volume > MAX_VOLUME)
        m_volume = MAX_VOLUME;

    ost << "volume is now -> " << m_volume << std::endl;
}

void MusicPlayer::DecreaseVol(size_t vol, std::ostream& ost)
{
    if (ost.bad())
        throw Object::ERROR_BAD_OSTREAM;

    if (vol > m_volume)
        m_volume = MIN_VOLUME;
    else
        m_volume -= vol;

    ost << "volume is now -> " << m_volume << std::endl;
}

void MusicPlayer::Add(std::string const& name, size_t const dur)
{
    m_songs.emplace_back(name, dur);
}
