#include "VideoPlayer.hpp"
#include <iterator>

void VideoPlayer::Play(std::ostream& ost) const {
	if (!ost.good()) throw VideoPlayer::ERROR_BAD_OSTREAM;
	if (m_CurrVid == m_Videos.cend()) throw VideoPlayer::ERROR_NO_SONG_IN_COLLECTION;

	ost << "playing video number" << CurIndex();
	ost << ": " << CurVideo();
	ost << " (" << (*m_CurrVid)->GetDurration() << ")" << std::endl;

	if (ost.fail()) throw VideoPlayer::ERROR_FAIL_WRITE;
}

void VideoPlayer::Stop(std::ostream& ost) const {
	if (!ost.good()) throw VideoPlayer::ERROR_BAD_OSTREAM;
	if (m_CurrVid == m_Videos.cend()) throw VideoPlayer::ERROR_NO_SONG_IN_COLLECTION;

	ost << "stop: video: " << (*m_CurrVid)->GetTitle();
	ost << " (" << (*m_CurrVid)->GetDurration() << ")" << std::endl;

	if (ost.fail()) throw VideoPlayer::ERROR_FAIL_WRITE;
}

bool VideoPlayer::First()
{
	if (m_Videos.empty()) return false;
	m_CurrVid = m_Videos.cbegin();
	return true;
}

bool VideoPlayer::Next()
{
	if (m_CurrVid == m_Videos.cend()) return false;
	m_CurrVid++;
	return true;
}

size_t VideoPlayer::CurIndex() const
{
	if (m_CurrVid == m_Videos.cend()) throw VideoPlayer::ERROR_NO_SONG_IN_COLLECTION;

	return  std::distance(m_Videos.cbegin(), m_CurrVid);
}

std::string VideoPlayer::CurVideo() const
{
	if (m_CurrVid == m_Videos.cend()) throw VideoPlayer::ERROR_NO_SONG_IN_COLLECTION;

	return (*m_CurrVid)->GetTitle();
}

void VideoPlayer::SetVolume(const size_t& vol, std::ostream& ost)
{
	if (!ost.good()) throw VideoPlayer::ERROR_BAD_OSTREAM;
	
	if (vol > MAX_VOLUME) m_volume = MAX_VOLUME;
	else				  m_volume = vol;

	ost << "volume is now -> " << m_volume;

	if (ost.fail()) throw VideoPlayer::ERROR_FAIL_WRITE;
}

size_t VideoPlayer::GetVolume() const
{
	return m_volume;
}

void VideoPlayer::Add(std::string const& name, size_t const dur, IVideoformat const * format)
{
	m_Videos.push_back(std::make_unique<Video>(Video{name,dur,format}));
}

