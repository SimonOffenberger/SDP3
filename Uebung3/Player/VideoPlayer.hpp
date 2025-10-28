#ifndef VIDEO_PLAYER_HPP
#define VIDEO_PLAYER_HPP

#include "Object.hpp"
#include "Video.hpp"
#include <vector>
#include <memory>
#include <iostream>

using TContVids = std::vector<std::unique_ptr<Video>>;

class VideoPlayer : public Object {
public:
	
	inline static const std::string ERROR_NO_SONG_IN_COLLECTION = "ERROR: No song in Player!";
	inline static const std::size_t MAX_VOLUME = 50;
	inline static const std::size_t MIN_VOLUME = 0;

	VideoPlayer(size_t default_vol = 8) : m_volume{ default_vol }{}

	void Play(std::ostream & ost = std::cout) const; 

	void Stop(std::ostream& ost = std::cout) const;
	
	bool First();

	bool Next();

	size_t CurIndex() const;

	std::string CurVideo() const;

	void SetVolume(const size_t & vol,std::ostream& ost = std::cout);

	size_t GetVolume() const;

	void Add(std::string const & name, size_t const dur,IVideoformat const * format);

private:
	size_t m_volume;
	TContVids m_Videos;
	TContVids::const_iterator m_CurrVid;
};

#endif // !VIDEO_PLAYER_HPP
