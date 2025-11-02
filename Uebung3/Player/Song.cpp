/*****************************************************************//**
 * \file   Song.cpp
 * \brief  Atomic Class for saving information about a song
 * \author Simon Vogelhuber
 * \date   October 2025
 *********************************************************************/

#include "Song.hpp"

Song::Song(const std::string& name, const size_t& dur)
{
    if (name.empty()) throw Song::ERROR_EMPTY_NAME;
    if (dur == 0)      throw Song::ERROR_DURATION_NULL;

    m_name = name;
    m_duration = dur;

}

std::string const& Song::GetTitle() const
{
    return m_name;
}

size_t const Song::GetDuration() const
{
    return m_duration;
}
