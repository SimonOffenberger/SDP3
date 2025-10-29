#include "VideoPlayerAdapter.hpp"

void VideoPlayerAdapter::Play(std::ostream & ost){
	m_player.Play(ost);
}

void VideoPlayerAdapter::VollInc(std::ostream& ost)
{
	m_player.SetVolume(m_player.GetVolume() + 1, ost);
}

void VideoPlayerAdapter::VollDec(std::ostream& ost)
{
	if (m_player.GetVolume() != 0) {
		m_player.SetVolume(m_player.GetVolume() - 1, ost);
	}
}

void VideoPlayerAdapter::Stop(std::ostream& ost)
{
	m_player.Stop(ost);
}

void VideoPlayerAdapter::Next()
{
	m_player.Next();
}

void VideoPlayerAdapter::Prev()
{
	const size_t currIndex = m_player.CurIndex();
	
	if (currIndex == 0) return;
	
	m_player.First();

	while (m_player.CurIndex() < (currIndex-1)) m_player.Next();
}


