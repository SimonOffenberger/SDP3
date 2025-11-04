/*****************************************************************//**
 * \file   MusicPlayer.hpp
 * \brief  MusicPlayer - A player for music!
 * \author Simon Vogelhuber
 * \date   October 2025
 *********************************************************************/
#ifndef MUSIC_PLAYER_HPP
#define MUSIC_PLAYER_HPP

#include "Object.hpp"
#include "Song.hpp"
#include <vector>

using  SongCollection = std::vector<Song>;

class MusicPlayer : public Object
{
public:
    // Exception constants
    inline static const std::string ERROR_DURATION_NULL = "ERROR: Song with duration 0!";
    inline static const std::string ERROR_EMPTY_NAME = "ERROR: Song with empty Name!";

	inline static const std::size_t MAX_VOLUME = 100;
	inline static const std::size_t MIN_VOLUME = 0;
    inline static const std::size_t DEFAULT_VOLUME = 50;

    /**
     * Default CTOR.
     * 
     */
    MusicPlayer() = default;

    /**
     * \brief Plays selected song
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
    size_t const GetCurIndex() const;
    /**
     * \brief Find song by name and selcet it
     * \param string name name of the Song
     * \return true if song by that name exists
     */
    bool Find(std::string const& name);

    /**
     * \brief Get No. Songs inside the player
     * \return size_t count of songs inside player
     */
    size_t const GetCount() const;

    /**
     * \brief Increase volume by 'vol' amount
     * \param size_t vol (volume)
     */
    void IncreaseVol(size_t const vol);

    /**
     * \brief Decrease volume by 'vol' amount
     * \param size_t vol (volume)
     */
    void DecreaseVol(size_t const vol);

    /**
     * \brief Add song to player
     * \param string name
     * \param size_t dur (duration)
     */
    void Add(std::string const& name, size_t const dur);

    // delete Copy Ctor and Assign Operator to prohibit untestet behaviour
    MusicPlayer(MusicPlayer& Music) = delete;
    void operator=(MusicPlayer Music) = delete;

private:
    SongCollection m_songs;
    size_t m_currentSongIdx = 0;
    size_t m_volume = DEFAULT_VOLUME;
};


#endif // !MUSIC_PLAYER_HPP