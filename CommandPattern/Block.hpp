#pragma once

#include "Object.hpp"
#include <memory>

class Block : public Object{
public: 
	using Wptr = std::weak_ptr<Block>;
	using Sptr = std::shared_ptr<Block>;

	void Move(int rel_x, int rel_y);

private:

	void Draw();

	size_t x = 0;
	size_t y = 0;
};
