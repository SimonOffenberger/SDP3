/*****************************************************************//**
 * \file   RPM_Sensor.cpp
 * \brief  A "sensor" for returning individual readings when
 * GetRevolutioins() is called.
 *
 * \author Simon
 * \date   November 2025
 *********************************************************************/

#include "RPM_Sensor.hpp"

unsigned int RPM_Sensor::GetRevolutions()
{
    unsigned int sensor_reading;

    if (m_fileStream.eof())
        throw ERROR_SENSOR_EOF;

    if (!(m_fileStream >> sensor_reading))
        throw ERROR_SENSOR_INVALID_DATA_INPUT;
    
    return sensor_reading;
}

RPM_Sensor::RPM_Sensor(std::string_view testFileName)
{
    m_fileStream = std::ifstream(testFileName.data());

    if (!m_fileStream.is_open())
        throw ERROR_SENSOR_FILE_NOT_FOUND;
}

RPM_Sensor::~RPM_Sensor()
{
    m_fileStream.close();
}
