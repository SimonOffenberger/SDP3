/*****************************************************************//**
 * \file   VideoPlayerAdapter.hpp
 * \brief  Adapter for the Video Player in order to Implement IPlayer Interface
 *
 * \author Simon
 * \date   November 2025
 *********************************************************************/
#ifndef VIDEO_PLAYER_ADAPTER_HPP
#define VIDEO_PLAYER_ADAPTER_HPP

#include "IPlayer.hpp"
#include "VideoPlayer.hpp"

class VideoPlayerAdapter : public Object, public IPlayer
{
public:

    /**
     * \brief Construct a VideoPlayer Adapter .
     * 
     * \param VidPlayer Reference to the actual VideoPlayer
     */
    VideoPlayerAdapter(VideoPlayer & VidPlayer) : m_player(VidPlayer) {}

    /**
     * \brief Play selected song
     */
    virtual void Play() override;

    /**
     * \brief increase volume by 1
     */
    virtual void VollInc() override;

    /**
     * \brief decrease volume by 1
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
    VideoPlayerAdapter(VideoPlayerAdapter& vid) = delete;
    void operator=(VideoPlayer vid) = delete;

private:
    VideoPlayer & m_player;
};

#endif // !MUSIC_PLAYER_ADAPTER_HPP