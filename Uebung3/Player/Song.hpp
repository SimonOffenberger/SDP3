#ifndef SONG_HPP
#define SONG_HPP

/*****************************************************************//**
 * \file   Song.hpp
 * \brief  Atomic Class for saving information about a song
 * \author Simon Vogelhuber
 * \date   October 2025
 *********************************************************************/

#include "Object.hpp"

class Song : public Object
{
public: 
    /**
     * \brief Get title of song
     * \return string - title of song
     */
    std::string const& GetTitle() const;
    
    /**
     * \brief Get duration of song
     * \return size_t - duratoin of song
     */
    size_t const GetDuration() const;
private:
    std::string m_name;
    size_t m_duration;
};

#endif // !SONG_HPP