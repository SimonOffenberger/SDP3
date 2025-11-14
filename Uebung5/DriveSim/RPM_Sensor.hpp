#ifndef RPM_SENSOR_HPP
#define RPM_SENSOR_HPP

#include <string>
#include <string_view>
#include <memory>

class RPM_Sensor {
public:

	using Sptr = std::shared_ptr<RPM_Sensor>;

	unsigned int GetRevolutioins() const;

	RPM_Sensor(std::string_view testFileName) : m_testFile{ testFileName } {}

private:
	const std::string m_testFile;
};

#endif // !RPM_SENSOR_HPP
