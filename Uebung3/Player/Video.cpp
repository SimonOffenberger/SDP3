/*****************************************************************//**
 * \file   Video.hpp
 * \brief  Implementation of a Video
 *
 * \author Simon
 * \date   November 2025
 *********************************************************************/
#include "Video.hpp"

Video::Video(const std::string& title, const size_t& duration, const EVideoFormat& format)
{
    if (title.empty()) throw Video::ERROR_EMPTY_NAME;
    if (duration == 0) throw Video::ERROR_DURATION_NULL;

    m_title = title;
    m_duration = duration;
    m_format = format;
}

const std::string & Video::GetTitle() const
{
    return m_title;
}

size_t Video::GetDuration() const
{
    return m_duration;
}

const std::string Video::GetFormatID() const
{
    switch (m_format) {
    case (EVideoFormat::AVI): return "AVI-Format";
    case (EVideoFormat::MKV): return "MKV-Format";
    case (EVideoFormat::WMV): return "WMV-Format";
    default: return "unkown Format";
    }
}

