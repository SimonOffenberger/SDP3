#include "Video.hpp"
#include <sstream>

std::string Video::GetTitle() const
{
    return m_title;
}

size_t Video::GetDurration() const
{
    return m_duration;
}

std::string Video::GetFormatID() const
{
    std::stringstream str;

    m_format->Print(str);

    return str.str();
}
