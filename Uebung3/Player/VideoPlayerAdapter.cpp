#include "VideoPlayerAdapter.hpp"

void VideoPlayerAdapter::Play(){
	m_player.Play();
}

void VideoPlayerAdapter::VollInc()
{
	m_player.SetVolume(m_player.GetVolume() + 1);
}

void VideoPlayerAdapter::VollDec()
{
	if (m_player.GetVolume() != 0) {
		m_player.SetVolume(m_player.GetVolume() - 1);
	}
}

void VideoPlayerAdapter::Stop()
{
	m_player.Stop();
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

void VideoPlayerAdapter::Select(std::string const& name)
{
	size_t prev_index = m_player.CurIndex();

	m_player.First();

	while (m_player.CurVideo() != name && m_player.Next());
	
	if (m_player.CurVideo() != name) std::cout << "video: " << name << " not found!" << std::endl;
	
}


