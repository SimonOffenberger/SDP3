#ifndef MUSIC_PLAYER_HPP
#define MUSIC_PLAYER_HPP


/*****************************************************************//**
 * \file   MusicPlayer.hpp
 * \brief  MusicPlayer - A player for music!
 * \author Simon Vogelhuber
 * \date   October 2025
 *********************************************************************/

#include "Object.hpp"
#include "Song.hpp"
#include <vector>

class MusicPlayer : public Object
{
public:
    /**
     * \brief Play selected song
     */
    void Start();

    /**
     * \brief Stop playing Song
     */
    void Stop();

    /**
     * \brief Skip to next song
     */
    void SwitchNext();

    /**
     * \brief Get index of current song
     * \return size_t of current's song index
     */
    size_t GetCurIndex();

    /**
     * \brief Find song by name
     * \return true if song by that name exists
     */
    bool Find(std::string name);

    /**
     * \brief Get No. Songs inside the player
     * \return size_t count of songs inside player
     */
    size_t GetCount();

    /**
     * \brief Increase volume by 'vol' amount
     * \param size_t vol (volume)
     */
    void IncreaseVol(size_t vol);

    /**
     * \brief Decrease volume by 'vol' amount
     * \param size_t vol (volume)
     */
    void DecreaseVol(size_t vol);

    /**
     * \brief Add song to player
     * \param string name
     * \param size_t dur (duration)
     */
    void Add(std::string name, size_t dur);
private:
    std::vector<Song> m_songs;
};


#endif // !MUSIC_PLAYER_HPP