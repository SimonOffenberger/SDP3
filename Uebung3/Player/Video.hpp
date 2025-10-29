#ifndef VIDEO_HPP
#define VIDEO_HPP

#include "Object.hpp"
#include "EVideoFormat.hpp"
#include <memory>


class Video : public Object
{
public:
	using Uptr = std::unique_ptr<Video>;
	using Sptr = std::shared_ptr<Video>;

	Video(const std::string & title,const size_t & duration,const EVideoFormat & format) : m_format(format) , m_title(title), m_duration(duration) {}

	std::string GetTitle() const;
	
	size_t GetDurration() const;

	std::string GetFormatID() const;

private:
	std::string m_title;
	size_t m_duration;
	EVideoFormat m_format;
};


#endif // !VIDEO_HPP