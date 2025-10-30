#ifndef VIDEO_PLAYER_HPP
#define VIDEO_PLAYER_HPP

#include "Object.hpp"
#include "Video.hpp"
#include <vector>
#include <memory>
#include <iostream>

using TContVids = std::vector<Video>;

class VideoPlayer : public Object {
public:
	
	inline static const std::string ERROR_NO_VIDEO_IN_COLLECTION = "ERROR: No video in Player!";
	inline static const std::size_t MAX_VOLUME = 50;
	inline static const std::size_t MIN_VOLUME = 0;
	inline static const std::size_t DEFAULT_VOLUME = 8;

	VideoPlayer(const size_t & default_vol = DEFAULT_VOLUME) : m_volume( default_vol ){}

	void Play() const; 

	void Stop() const;
	
	bool First();

	bool Next();

	size_t CurIndex() const;

	std::string CurVideo() const;

	void SetVolume(const size_t & vol);

	size_t GetVolume() const;

	void Add(std::string const & name, size_t const dur,EVideoFormat const & format);

private:
	size_t m_volume;
	TContVids m_Videos;
	size_t m_curIndex = 0;
};

#endif // !VIDEO_PLAYER_HPP
