#ifndef VIDEO_PLAYER_ADAPTER_HPP
#define VIDEO_PLAYER_ADAPTER_HPP

#include "IPlayer.hpp";
#include "VideoPlayer.hpp"

class VideoPlayerAdapter : public Object, public IPlayer
{
public:

    VideoPlayerAdapter(VideoPlayer& VidPlayer) : m_player(VidPlayer) {}

    /**
     * \brief Play selected song
     */
    virtual void Play(std::ostream& ost = std::cout) override;

    /**
     * \brief increase volume by 1 (out of 100)
     */
    virtual void VollInc(std::ostream& ost = std::cout) override;

    /**
     * \brief decrease volume by 1 (out of 100)
     */
    virtual void VollDec(std::ostream& ost = std::cout) override;

    /**
     * \brief Stop playing Song
     */
    virtual void Stop(std::ostream& ost = std::cout) override;

    /**
     * \Skip to next song
     */
    virtual void Next() override;

    /**
     * \brief Skip to previous song
     */
    virtual void Prev() override;

private:
    VideoPlayer & m_player;
};

#endif // !MUSIC_PLAYER_ADAPTER_HPP