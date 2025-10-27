#ifndef IVIDEO_FORMAT_HPP
#define IVIDEO_FORMAT_HPP


class IVideoformat
{
public:
	virtual void Print(std::ostream & ost) const = 0;

	virtual ~IVideoformat() = default;
};


#endif // !IVIDEO_FORMAT_HPP