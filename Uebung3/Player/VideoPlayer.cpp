/*****************************************************************//**
 * \file   VideoPlayer.cpp
 * \brief  Implementation of Video Player of the Company DonkySoft
 *
 * \author Simon Offenberger
 * \date   November 2025
 *********************************************************************/
#include "VideoPlayer.hpp"
#include <iostream>

void VideoPlayer::Play() const {
	if (!std::cout.good()) throw VideoPlayer::ERROR_BAD_OSTREAM;
	if (m_Videos.empty()) {
		std::cout << "no video in playlist!" << std::endl;
		return;
	}

	std::cout << "playing video number" << CurIndex();
	std::cout << ": " << CurVideo();
	std::cout << " [" << m_Videos.at(m_curIndex).GetDuration() << "min]" << std::endl;

	if (std::cout.fail()) throw VideoPlayer::ERROR_FAIL_WRITE;
}

void VideoPlayer::Stop() const {
	if (!std::cout.good()) throw VideoPlayer::ERROR_BAD_OSTREAM;
	if (m_Videos.empty()) {
		std::cout << "no video in playlist!" << std::endl;
		return;
	}

	std::cout << "stop: video: " << CurVideo();
	std::cout << " [" << m_Videos.at(m_curIndex).GetDuration() << "min]" << std::endl;

	if (std::cout.fail()) throw VideoPlayer::ERROR_FAIL_WRITE;
}

bool VideoPlayer::First()
{
	if (m_Videos.empty()) return false;

	m_curIndex = 0;

	return true;
}

bool VideoPlayer::Next()
{
	m_curIndex++;

	if (m_curIndex >= m_Videos.size()) {
		m_curIndex = m_Videos.size() - 1;
		return false;
	}
	else {
		return true;
	}
}

size_t VideoPlayer::CurIndex() const
{
	if (m_Videos.size()==0)	throw VideoPlayer::ERROR_NO_VIDEO_IN_COLLECTION;

	return  m_curIndex;
}

std::string const VideoPlayer::CurVideo() const
{
	if (m_Videos.size()==0)	throw VideoPlayer::ERROR_NO_VIDEO_IN_COLLECTION;

	return m_Videos.at(m_curIndex).GetTitle();
}

void VideoPlayer::SetVolume(const size_t vol)
{
	if (!std::cout.good()) throw VideoPlayer::ERROR_BAD_OSTREAM;
	
	if (vol > MAX_VOLUME) m_volume = MAX_VOLUME;
	else				  m_volume = vol;

	std::cout << "volume is now -> " << m_volume;

	if (std::cout.fail()) throw VideoPlayer::ERROR_FAIL_WRITE;
}

size_t const VideoPlayer::GetVolume() const
{
	return m_volume;
}

void VideoPlayer::Add(std::string const& name, size_t const dur, EVideoFormat const & format)
{
	if (name.empty()) throw VideoPlayer::ERROR_EMPTY_NAME;
	if (dur == 0) throw VideoPlayer::ERROR_DURATION_NULL;

	m_Videos.emplace_back(name,dur,format);
}

