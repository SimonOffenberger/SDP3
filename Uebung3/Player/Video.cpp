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
    switch (m_format) {
    case (EVideoFormat::AVI): return "AVI-Format";
    case (EVideoFormat::MKV): return "MKV-Format";
    case (EVideoFormat::WMV): return "WMV-Format";
    default: return "unkown Format";
    }
}

