/*****************************************************************//**
 * \file   IPlayer.hpp
 * \brief  Interface to interact with various Player (music, video)
 * \author Simon Vogelhuber
 * \date   October 2025
 *********************************************************************/

class IPlayer
{
public:
    /**
     * \brief Play selected song 
     */
    virtual void Play() = 0;
    
    /**
     * \brief increase volume by 1 (out of 100)
     */
    virtual void VollInc() = 0;
    
    /**
     * \brief decrease volume by 1 (out of 100)
     */
    virtual void VollDec() = 0;
    
    /**
     * \brief Stop playing Song
     */
    virtual void Stop() = 0;
    
    /**
     * \brief Skip to next song
     */
    virtual void Next() = 0;
    
    /**
     * \brief Skip to previous song
     */
    virtual void Prev() = 0;
};