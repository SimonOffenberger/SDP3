/*****************************************************************//**
 * \file   Video.hpp
 * \brief  Implementation of a Video
 * 
 * \author Simon
 * \date   November 2025
 *********************************************************************/
#ifndef VIDEO_HPP
#define VIDEO_HPP

#include "Object.hpp"
#include "EVideoFormat.hpp"

class Video : public Object
{
public:

	// Exceptions 
	inline static const std::string ERROR_DURATION_NULL = "ERROR: Video with duration 0!";
	inline static const std::string ERROR_EMPTY_NAME = "ERROR: Video with empty Name!";

	/**
	 * \brief CTOR of a Video.
	 * 
	 * \param title Tilte of the Video
	 * \param duration Duration of the Video in min
	 * \param format Video Format can be of Type EVideoFormat
	 * \throw ERROR_DURATION_NULL
	 * \throw ERROR_EMPTY_NAME
	 */
	Video(const std::string& title, const size_t& duration, const EVideoFormat& format);

	/**
	 * \brief Getter of the Video Title.
	 * 
	 * \return Video Title
	 */
	const std::string & GetTitle() const;
	
	/**
	 * \brief Getter of the Video duration
	 * 
	 * \return duration of the video
	 */
	size_t GetDuration() const;

	/**
	 * \brief Getter for the String Identifier of the Format.
	 * 
	 * \return String of the Video Format
	 */
	const std::string GetFormatID() const;

private:
	std::string m_title;
	size_t m_duration;
	EVideoFormat m_format;
};


#endif // !VIDEO_HPP