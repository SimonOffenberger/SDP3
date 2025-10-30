#ifndef MUSIC_PLAYER_ADAPTER_HPP
#define MUSIC_PLAYER_ADAPTER_HPP

#include "IPlayer.hpp"
#include "MusicPlayer.hpp"

class MusicPlayerAdapter : public IPlayer
{
public:

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

    virtual void Select(std::string const& name) override;
    
private:
    MusicPlayer & m_player;
};

#endif // !MUSIC_PLAYER_ADAPTER_HPP