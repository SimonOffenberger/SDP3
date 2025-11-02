/*****************************************************************//**
 * \file   Song.hpp
 * \brief  Atomic Class for saving information about a song
 * \author Simon Vogelhuber
 * \date   October 2025
 *********************************************************************/
#ifndef SONG_HPP
#define SONG_HPP

#include "Object.hpp"

class Song : public Object
{
public: 

    // Exceptions 
    inline static const std::string ERROR_DURATION_NULL = "ERROR: Song with duration 0!";
    inline static const std::string ERROR_EMPTY_NAME = "ERROR: Song with empty Name!";

    Song(const std::string& name, const size_t& dur);
    /**
     * \brief Get title of song
     * \return string - title of song
     * \throw ERROR_DURATION_NULL
     * \throw ERROR_EMPTY_NAME
     */
    std::string const& GetTitle() const;
    
    /**
     * \brief Get duration of song
     * \return size_t - duratoin of song
     */
    size_t const GetDuration() const;
private:
    std::string  m_name;
    size_t  m_duration;
};

#endif // !SONG_HPP