/*****************************************************************//**
 * \file   IPlayer.hpp
 * \brief  Interface to interact with various Player (music, video)
 * \author Simon Vogelhuber
 * \date   October 2025
 *********************************************************************/
#ifndef IPLAYER_HPP
#define IPLAYER_HPP

#include <string>

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

    /**
     * \brief Selects a Video by Name.
     *
     * \param name
     */
    virtual void Select(std::string const& name) = 0;

    /**
     * \brief virtual Destructor for Interface.
     * 
     */
    virtual ~IPlayer() = default;

};


#endif // !IPLAYER_HPP