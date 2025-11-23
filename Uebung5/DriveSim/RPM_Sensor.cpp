/*****************************************************************//**
 * \file   RPM_Sensor.cpp
 * \brief  A "sensor" for returning individual readings when
 * GetRevolutioins() is called.
 *
 * \author Simon
 * \date   November 2025
 *********************************************************************/

#include "RPM_Sensor.hpp"

#include <algorithm>
#include <sstream>

size_t RPM_Sensor::GetRevolutions()
{
    std::string sensor_reading;
    std::stringstream converter;
    size_t sensor_value = 0;

    if (m_fileStream.eof())
        throw ERROR_SENSOR_EOF;

    if(m_fileStream.fail())
        throw ERROR_SENSOR_INVALID_DATA_INPUT;

    m_fileStream >> sensor_reading;

    if (sensor_reading.empty())
        throw ERROR_SENSOR_INVALID_DATA_INPUT;

    // check if all of the readings are digits
    if (!std::all_of(sensor_reading.cbegin(), sensor_reading.cend(), ::isdigit))
        throw ERROR_SENSOR_INVALID_DATA_INPUT;

    // use Stringstream for type Conversion
    converter << sensor_reading;
    converter >> sensor_value;
    
    return sensor_value;
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
