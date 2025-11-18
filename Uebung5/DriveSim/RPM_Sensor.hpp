/*****************************************************************//**
 * \file   RPM_Sensor.hpp
 * \brief  A "sensor" for returning individual readings when 
 * GetRevolutioins() is called.		
 * 
 * \author Simon
 * \date   November 2025
 *********************************************************************/

#ifndef RPM_SENSOR_HPP
#define RPM_SENSOR_HPP

#include <string>
#include <string_view>
#include <memory>
#include <fstream>

class RPM_Sensor {
public:
	inline static const std::string ERROR_SENSOR_FILE_NOT_FOUND = "ERROR RPM sensor file was not found";
	inline static const std::string ERROR_SENSOR_INVALID_DATA_INPUT = "ERROR RPM sensor could not read data from file.";
	inline static const std::string ERROR_SENSOR_EOF = "ERROR RPM sensor file has ended, theres no more data.";

	/**
	 * \brief Shared pointer tyope for RPM_Sensor
	 */
	using Sptr = std::shared_ptr<RPM_Sensor>;

	/**
	 * \brief Returns current rpm. This is achieved by parsing 
	 * from a testfile - if the end of the fiel is reached a
	 * exception is thrown (ERROR_SENSOR_EOF). This has to
	 * be handled by the user of this class.
	 * \return unsigned int revs 
	 */
	unsigned int GetRevolutioins();

	/**
	 * \brief RPM_Sensor constructor
	 * throws error (ERROR_SENSOR_FILE_NOT_FOUND)
	 * if the provided file/path is invalid.
	 */
	RPM_Sensor(std::string_view testFileName);

	/**
	 * \brief custom destructor is needed to
	 * close ifstream.
	 */
	~RPM_Sensor();
private:
	// open a filestream when sensor is constructed
	// close when destructor is called.
	std::ifstream m_fileStream;
};

#endif // !RPM_SENSOR_HPP
