#ifndef VIDEO_HPP
#define VIDEO_HPP

#include "Object.hpp"
#include "IVideoFormat.hpp"
#include <memory>


class Video : public Object
{
public:

	Video(const std::string & title,const size_t & duration,IVideoformat const * format) : m_format(std::move(format)) , m_title(title), m_duration(duration) {}

	using UPtr = std::unique_ptr<const IVideoformat>;

	std::string GetTitle() const;
	
	size_t GetDurration() const;

	std::string GetFormatID() const;

private:
	std::string m_title;
	size_t m_duration;
	UPtr m_format;
};


#endif // !VIDEO_HPP