/*****************************************************************//**
 * \file   MusicPlayerAdapter.hpp
 * \brief  Adapter for a Musicplayer to comply with Interface IPlayer
 * 
 * \author Simon
 * \date   November 2025
 *********************************************************************/
#ifndef MUSIC_PLAYER_ADAPTER_HPP
#define MUSIC_PLAYER_ADAPTER_HPP

#include "IPlayer.hpp"
#include "MusicPlayer.hpp"

class MusicPlayerAdapter :public Object, public IPlayer
{
public:

    /**
     * \brief Ctor for Adapter.
     * 
     * \param player Reference to a MusicPlayer
     */
    MusicPlayerAdapter(MusicPlayer & player) : m_player{ player } {}

    /**
     * \brief Play selected song
     */
    virtual void Play() override;

    /**
     * \brief increase volume by 1 (out of 100)
     */
    virtual void VollInc() override;

    /**
     * \brief decrease volume by 1 (out of 100)
     */
    virtual void VollDec() override;

    /**
     * \brief Stop playing Song
     */
    virtual void Stop() override;

    /**
     * \Skip to next song
     */
    virtual void Next() override;

    /**
     * \brief Skip to previous song
     */
    virtual void Prev() override;

    /**
     * \brief Selects a Video by Name.
     *
     * \param name
     */
    virtual void Select(std::string const& name) override;

    // delete Copy Ctor and Assign Operator to prohibit untestet behaviour
    MusicPlayerAdapter(MusicPlayerAdapter& Music) = delete;
    void operator=(MusicPlayerAdapter Music) = delete;
    
private:
    MusicPlayer & m_player;
};

#endif // !MUSIC_PLAYER_ADAPTER_HPP