/*****************************************************************//**
 * \file   VideoPlayer.hpp
 * \brief  Implementation of Video Player of the Company DonkySoft
 * 
 * \author Simon Offenberger
 * \date   November 2025
 *********************************************************************/
#ifndef VIDEO_PLAYER_HPP
#define VIDEO_PLAYER_HPP

#include "Object.hpp"
#include "Video.hpp"
#include <vector>
#include <memory>
#include <iostream>

// Using definition of the container
using TContVids = std::vector<Video>;

class VideoPlayer : public Object {
public:
	// defintion of Error Messagnes and constance
	inline static const std::string ERROR_NO_VIDEO_IN_COLLECTION = "ERROR: No video in Player!";
	inline static const std::string ERROR_DURATION_NULL = "ERROR: Video with duration 0!";
	inline static const std::string ERROR_EMPTY_NAME = "ERROR: Video with empty Name!";

	inline static const std::size_t MAX_VOLUME = 50;
	inline static const std::size_t MIN_VOLUME = 0;
	inline static const std::size_t DEFAULT_VOLUME = 8;

	/**
	 * \brief Starts playing the selected Video.
	 * \throw ERROR_BAD_OSTREAM
	 * \throw ERROR_FAIL_WRITE
	 */
	void Play() const; 

	/**
	 * \brief Stops the selected Video.
	 * \throw ERROR_BAD_OSTREAM
	 * \throw ERROR_FAIL_WRITE
	 */
	void Stop() const;
	
	/**
	 * \brief Switches to the first video in the collection.
	 * 
	 * \return true -> if videos are in the playlist
	 * \return false -> no video in the playlist
	 */
	bool First();

	/**
	 * \brief Switches to the next video.
	 * 
	 * \return true -> switch was successful
	 * \return false -> no switch possiple index at top of playlist
	 */
	bool Next();

	/**
	 * \brief returns the current index of the selected video.
	 * 
	 * \return Index of the current video
	 * \throw ERROR_NO_VIDEO_IN_COLLECTION
	 */
	size_t CurIndex() const;

	/**
	 * \brief Get the name of the current video.
	 * 
	 * \return String identidier of the video
	 * \throw ERROR_NO_VIDEO_IN_COLLECTION
	 */
	std::string const CurVideo() const;

	/**
	 * \brief sets the volume of the player to a specified value.
	 
	 * \param vol Volume is bond to VideoPlayer::MAX_VOLUME to VideoPlayer::MIN_VOLUME
	 * \throw ERROR_BAD_OSTREAM 
	 * \throw ERROR_FAIL_WRITE
 	 */
	void SetVolume(const size_t vol);

	/**
	 * \brief Returns the curreunt volume of the player.
	 * 
	 * \return Volume of the player
	 */
	size_t const GetVolume() const;

	/**
	 * \brief Adds a Video to the VideoPlayer.
	 * 
	 * \param name Name of the Video
	 * \param dur Duration of the Video in min
	 * \param format Video Format
	 * \throw ERROR_EMPTY_NAME
	 * \throw ERROR_DURATION_NULL
	 */
	void Add(std::string const & name, size_t const dur,EVideoFormat const & format);

private:
	size_t m_volume = DEFAULT_VOLUME;
	TContVids m_Videos;
	size_t m_curIndex = 0;
};

#endif // !VIDEO_PLAYER_HPP
