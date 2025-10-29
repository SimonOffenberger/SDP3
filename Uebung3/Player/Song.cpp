/*****************************************************************//**
 * \file   Song.cpp
 * \brief  Atomic Class for saving information about a song
 * \author Simon Vogelhuber
 * \date   October 2025
 *********************************************************************/

#include "Song.hpp"

std::string const& Song::GetTitle() const
{
    return m_name;
}

size_t const Song::GetDuration() const
{
    return m_duration;
}
