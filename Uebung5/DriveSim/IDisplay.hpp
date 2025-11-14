#ifndef IDISPLAY_HPP
#define IDISPLAY_HPP

#include <memory>

class IDisplay{
public:
	using Sptr = std::shared_ptr<IDisplay>;

	virtual	void Update() = 0;

	virtual ~IDisplay() = default;

protected:
	IDisplay() = default;
};

#endif // !IDISPLAY_HPP